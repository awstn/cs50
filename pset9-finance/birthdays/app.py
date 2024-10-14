import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session


# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True
#Ensure that the cookie is deleted when you close the browser
app.config["SESSION_PERMANENT"] = False
# Ensure that the contents of your "shopping cart" is stored in the server and not as a cookie
# For privacy sake
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")

@app.after_request
def after_request(response):
    #Ensure responses aren't cached
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":

        # TODO: Add the user's entry into the database
        name = request.form.get("name")
        month = request.form.get("month")
        day = request.form.get("day")

        # If user enters nothing in the fields. 
        if not name or not month or not day:
            flash("Incorrect values")
            return redirect("/")

        # If user enters month or day that is not applicable 
        elif int(month) > 12 or int(month) < 1 or int(day) < 1 or int(day) > 31:
            flash("Incorrect values")
            return redirect("/")

        db.execute("INSERT INTO birthdays (name, month, day) VALUES(?, ?, ?)", name, month, day)
                      
        return redirect("/")

    else:
        # TODO: Display the entries in the database on index.html
        rows = db.execute("SELECT * FROM birthdays")

        return render_template("index.html", birthdays=rows)

@app.route("/delete", methods=["POST"])
def delete():
    id = request.form.get("id")        
    if id:
        db.execute("DELETE FROM birthdays where id = ?", id)
        flash('Item deleted.')
        
        return redirect("/")

    







 