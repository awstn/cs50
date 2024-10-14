from cs50 import SQL
from datetime import datetime


db = SQL("sqlite:///finance.db")

def getUserHoldings(user_id: str):
    userHoldings = db.execute("""SELECT 
                                symbol, TOTAL(share) as share, share_cost as share_cost, TOTAL(total_cost) as total_cost
                                FROM transactions
                                WHERE user_id = ?
                                GROUP BY symbol
                                HAVING sum(share) > 0""", user_id)

    #db.execute returns a list of dictionaries
    return userHoldings

def getUserBalance(userHoldings: list, user_id: str):
    stockBalance = 0
    for row in userHoldings:           
        stockBalance += row["total_cost"]   

    # Add the users cash balance and grand total
    cashBalance = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
    cashBalance = int(cashBalance[0]["cash"])

    totalBalance = cashBalance + stockBalance

    return cashBalance, totalBalance

def addTransaction(user_id, symbol, share, sharePrice, buyRequest, updatedCashBalance):
    db.execute("INSERT INTO transactions (user_id, symbol, share, share_cost, total_cost) VALUES (?, ?, ?, ?, ?)", 
                user_id, symbol, share, sharePrice, buyRequest)
    
    db.execute("UPDATE users SET cash = ? WHERE id = ?", updatedCashBalance, user_id)

def getUserTransactions(user_id: str):
    userHoldings = db.execute("""SELECT 
                                symbol, share, share_cost as share_cost, created_at
                                FROM transactions
                                WHERE user_id = ?
                                ORDER BY created_at DESC""", user_id)

    #db.execute returns a list of dictionaries
    return userHoldings