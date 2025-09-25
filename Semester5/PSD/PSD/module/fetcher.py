import mysql.connector as myconnector
import psycopg2 as pgconnector

def mysqlConnection():
    return myconnector.connect(
        host="localhost",
        port=3306,
        user="root",
        password="",
        database="iris_db"
    ) 

def pgConnection():
    return pgconnector.connect("host=localhost user=postgres password=zanra2401 dbname=iris_db port=2005")

def fetchDataMysql(query):
    connection = mysqlConnection()
    cursor = connection.cursor()

    cursor.execute(query)
    data = cursor.fetchall()

    cursor.close()
    connection.close()

    return data

def fetchDataPg(query):
    connection = pgConnection()
    cursor = connection.cursor()

    cursor.execute(query)
    data = cursor.fetchall()

    cursor.close()
    connection.close()

    return data
