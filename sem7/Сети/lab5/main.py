import smtplib as smtp
import sys
from email.mime.application import MIMEApplication
from email.mime.text import MIMEText
from getpass import getpass
import os
from email.mime.multipart import MIMEMultipart
from os.path import basename


def findFiles(key):
    files = []
    path = os.getcwd()

    for item in os.listdir(path):
        if item.find(key) != -1:
            files.append(item)

    return files


def main():
    print(sys.argv)
    if len(sys.argv) <= 1:
        email = input('введите почту: ')
        password = getpass('введите пароль: ')
        dest_email = input('введите адрес получателя: ')
        subject = input('тема письма: ')
        email_text = input('текст письма: ' )
        server_address = input('адрес smtp сервера: ')
        key_word = input('введите ключевое слово: ')
    elif len(sys.argv) == 8:
        email = sys.argv[1]
        password = sys.argv[2]
        dest_email = sys.argv[3]
        subject = sys.argv[4]
        email_text = sys.argv[5]
        server_address = sys.argv[6]
        key_word = sys.argv[7]
    else:
        print("WRONG CMD: python3 main.py from_email password to_email subject message server_address key")
        exit(1)

    files = findFiles(key_word)

    if len(files) == 0:
        print("No such files.")

    msg = MIMEMultipart()
    msg['From'] = email
    msg['To'] = dest_email
    msg['Subject'] = subject

    for file in files:
        with open(file, "rb") as fil:
            part = MIMEApplication(
                fil.read(),
                Name=basename(file)
            )
        part['Content-Disposition'] = 'attachment; filename="%s"' % basename(file)
        msg.attach(part)

    msg.attach(MIMEText(email_text, 'plain'))
    server = smtp.SMTP_SSL(server_address) # for example smtp.yandex.com
    server.set_debuglevel(1)
    server.ehlo(email)
    server.login(email, password)
    server.auth_plain()
    server.sendmail(email, dest_email, msg.as_string())
    server.quit()


if __name__ == '__main__':
    main()
