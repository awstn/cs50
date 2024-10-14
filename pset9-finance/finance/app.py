import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd
from dbhelpers import getUserHoldings, getUserBalance, addTransaction, getUserTransactions

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET"])
@login_required
def index():
    """Show portfolio of stocks"""
    if request.method == "GET":
        userHoldings = getUserHoldings(session["user_id"])
        cashBalance, totalBalance = getUserBalance(userHoldings, session["user_id"])
        
        # Check if user is logged in. Else redirect to login page
        if "username" in session:
            return render_template("index.html", user=session["username"], 
                                   userHoldings=userHoldings, 
                                   cashBalance=cashBalance, 
                                   totalBalance=totalBalance)
        
        else:
            redirect("/login")

    return apology("Homepage Error")


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    if request.method == "POST":
        symbol = request.form.get("symbol")
        share = request.form.get("shares")
        
        # Convert symbol to uppercase and strip whitespace
        symbol = symbol.upper().strip()
        # Lookup share through Yahoo API using lookup() function
        search = lookup(symbol)

        if search is None:
            return apology("Stock does not exist")
        if not share.isdigit():
            return apology("You cannot purchase partial shares.")
        if int (share) < 0:
            return apology("Cannot purchase a negative amount")
        
        sharePrice = float(search["price"])
        buyRequest = sharePrice * int(share)

        # Get cash balance of current user 
        userHoldings = getUserHoldings(session["user_id"])
        cashBalance = getUserBalance(userHoldings, session["user_id"])[0]
        
        # Check if user has enough in their balance to purchase their order
        if buyRequest > cashBalance:
            return apology("You do not have enough funds in your account")
        
        # Updated balance after purchasing share
        updatedCashBalance = cashBalance - buyRequest
        addTransaction(session["user_id"], symbol, share, sharePrice, buyRequest, updatedCashBalance)
        return redirect("/")
    
    else:
        return render_template("buy.html")

@app.route("/history", methods=["GET"])
@login_required
def history():
    if request.method == "GET":
        userTransactions = getUserTransactions(session["user_id"])
    
        # Check if user is logged in. Else redirect to login page
        if "username" in session:
            return render_template("history.html", user=session["username"], 
                                    userHoldings=userTransactions)
    
    else:
        redirect("/login")

    return apology("History Error")


@app.route("/login", methods=["GET", "POST"])
def login():
    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]
        session["username"] = rows[0]["username"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    #error = None
    if request.method == "POST":
        stockSymbol = request.form.get("symbol")
        results = lookup(stockSymbol)
        if results is None:
            return apology("Symbol not found")
            #error = "Stock not found"
            #return render_template("quote.html", error=error)
        
        return render_template("quoted.html", stock=results)
    
    else:
        return render_template("quote.html")

@app.route("/register", methods=["GET", "POST"])    
def register():
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")
        # Ensure username is not blank
        if not username:
            return apology("Username is blank")

        rows = db.execute("SELECT * FROM users")
        # Ensure username is unique
        for i in rows:
            if username == i["username"]:
                return apology("Username is taken")
        # Ensure password is not blank
        if not password:
            return apology("Password is blank")
        # Ensure password and confirmation match
        if confirmation != password:
            return apology("Passwords do not match")
        
        hash:int = generate_password_hash(password, method='pbkdf2', salt_length=16)

        db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", username, hash)

        return redirect("/")
    return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    userHoldings = getUserHoldings(session["user_id"])

    if request.method == "POST":
        symbol = request.form.get("symbol")
        shareQuantity = int(request.form.get("shares"))
        
        if shareQuantity < 0:
            return apology("Cannot sell a negative amount")
        
        symbolFound = False
        for holding in userHoldings:
            if holding["symbol"] == symbol:
                symbolFound = True
                if shareQuantity > holding["share"]:
                    return apology("You do not own enough shares.")

        if not symbolFound:
            return apology("Selection not found")
                           
        share_cost = float(lookup(symbol)["price"])
        sellRequest = share_cost * shareQuantity
        shareQuantity = -1 * shareQuantity

        # Get cash balance of current user 
        cashBalance = getUserBalance(userHoldings, session["user_id"])[0]
        updatedCashBalance = cashBalance + sellRequest
        sellRequest = sellRequest * -1
        
        addTransaction(session["user_id"], symbol, shareQuantity, share_cost, sellRequest, updatedCashBalance)
        return redirect("/")

    else:
        return render_template("sell.html", stocksOwned=userHoldings)



