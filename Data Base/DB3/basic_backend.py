import mvc_exceptions as mvc_exc
import psycopg2
import datetime as DT
from config import DATABASE_URI

from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy import Column, Integer, String, Date, Boolean, ForeignKey

from sqlalchemy import create_engine
from contextlib import contextmanager
from sqlalchemy.orm import sessionmaker
from sqlalchemy import event, DDL

engine = create_engine(DATABASE_URI)
Base = declarative_base()
Session = sessionmaker(bind=engine)


@contextmanager
def session_scope():
    session = Session()
    try:
        yield session
        session.commit()
    except Exception:
        session.rollback()
        raise
    finally:
        session.close()


class Users(Base):
    __tablename__ = 'users'
    user_id = Column(Integer, primary_key=True)
    username = Column(String)
    phone_number = Column(Integer)

    __mapper_args__ = {
        'confirm_deleted_rows': False
    }

    def __repr__(self):
        return f"users (user_id='{self.user_id}', username='{self.username}', phone_number='{self.phone_number}')"


class Email(Base):
    __tablename__ = 'email'
    email_id = Column(Integer, primary_key=True)
    user_id = Column(Integer, ForeignKey('users.user_id'))
    email_adress = Column(String)
    email_type = Column(String)

    def __repr__(self):
        return f"email (email_id='{self.email_id}', users_id='{self.user_id}', email_address='{self.email_adress}', " \
               f"email_type='{self.email_type}')"


class Folders(Base):
    __tablename__ = 'folders'
    folders_id = Column(Integer, primary_key=True)
    email_id = Column(Integer, ForeignKey('email.email_id'))
    folder_name = Column(String)
    folder_type = Column(String)

    def __repr__(self):
        return f"folders (folders_id='{self.folders_id}', email_id='{self.email_id}', " \
               f"folder_name='{self.folder_name}', folder_type='{self.folder_type}')"


class FolMes(Base):
    __tablename__ = 'folders_messages'
    folders_id = Column(Integer, primary_key=True, unique=False)
    messages_id = Column(Integer, ForeignKey('messages.messages_id'), unique=False)

    def __repr__(self):
        return f"Folders_messages (folders_id='{self.folders_id}', messages_id='{self.messages_id}')"


class Messages(Base):
    __tablename__ = 'messages'
    messages_id = Column(Integer, primary_key=True)
    read_or_not = Column(Boolean)
    message_name = Column(String)
    message_date = Column(Date)

    def __repr__(self):
        return f"messages (messages_id='{self.messages_id}', read_or_not='{self.read_or_not}', " \
               f"message_name='{self.message_name}', message_date='{self.message_date}')"


def table_check(table_name):
    if table_name == 'users':
        return Users
    elif table_name == 'email':
        return Email
    elif table_name == 'folders':
        return Folders
    elif table_name == 'folders_messages':
        return FolMes
    elif table_name == 'messages':
        return Messages
    else:
        raise mvc_exc.WrongInput(f"Table name '{table_name}' doesn't exist!")


def get_all_keys(table_name):
    with session_scope() as s:
        col_names = table_name.__table__.columns.keys()
    return col_names


def create_item(table_name, *value):
    keys = get_all_keys(table_name)

    i = 0
    for key in keys:
        d = getattr(table_name, key).type
        if type(d) is Integer:
            d = 0
        elif type(d) is Boolean:
            d = False
        elif type(d) is Date:
            d = DT.datetime.strptime('2020,1,1', '%Y,%m,%d').date()
        elif type(d) is String:
            d = 'str'
        if type(d) != type(value[i]):
            raise mvc_exc.ValueTypeError(f"Value: <{value[i]}> must be the same type as key!")
        i = i + 1

    with session_scope() as s:
        check_id = {keys[0]: value[0]}
        check = s.query(table_name).filter_by(**check_id).all()

        if not check:
            check_items = {keys[i]: value[i] for i in range(1, len(keys))}
        else:
            raise mvc_exc.ItemAlreadyStored(
                f"Can't create item with {keys[0]} = {value[0]} because it is already exists")

        check = s.query(table_name).filter_by(**check_items).all()
        if not check:
            create_it = {}
            i = 0
            for key in keys:
                create_it[key] = value[i]
                i = i + 1
        else:
            raise mvc_exc.ItemAlreadyStored(f"Can't create item because all data for its id {keys[0]} = {value[0]} "
                                            f"already exists")

        s.add(table_name(**create_it))


def read_item(table_name, **name):
    with session_scope() as s:
        keys = get_all_keys(table_name)
        for key, value in name.items():
            f = False

            for item in keys:
                if key == item:
                    f = True
                    d = getattr(table_name, key).type
                    if type(d) is Integer:
                        d = 0
                    elif type(d) is Boolean:
                        d = False
                    elif type(d) is Date:
                        d = DT.datetime.strptime('2020,1,1', '%Y,%m,%d').date()
                    elif type(d) is String:
                        d = 'str'
                    if type(d) != type(value):
                        raise mvc_exc.ValueTypeError(f"Value: <{value}> must be the same type as key!")

            if f is False:
                raise mvc_exc.KeyNameError(f"Key: <{key}> doesn't exist in table '{table_name.__tablename__}'!")

        read_it = s.query(table_name).filter_by(**name).all()

        if not read_it:
            raise mvc_exc.ItemNotStored(f"{name.items()} not stored")

        for rows in read_it:
            print(rows)


def read_items(table_name):
    with session_scope() as s:
        keys = get_all_keys(table_name)
        read_all = s.query(table_name).order_by(getattr(table_name, keys[0]).asc()).all()

        if not read_all:
            print(f"Table {table_name} is empty")
        for row in read_all:
            print(row)


def update_item(table_name, new_value, **name):
    with session_scope() as s:
        keys = get_all_keys(table_name)
        for key, value in name.items():
            f = False

            for item in keys:
                if key == item:
                    f = True
                    d = getattr(table_name, key).type
                    if type(d) is Integer:
                        d = 0
                    elif type(d) is Boolean:
                        d = False
                    elif type(d) is Date:
                        d = DT.datetime.strptime('2020,1,1', '%Y,%m,%d').date()
                    elif type(d) is String:
                        d = 'str'

                    if type(d) != type(value):
                        raise mvc_exc.ValueTypeError(f"Value: <{value}> must be the same type as key!")
                    elif type(d) != type(new_value):
                        raise mvc_exc.ValueTypeError(f"Value: <{new_value}> must be the same type as key!")

            if f is False:
                raise mvc_exc.KeyNameError(f"Key: <{key}> doesn't exist in table '{table_name.__tablename__}'!")

        try:
            update_it = s.query(table_name).filter_by(**name).one()
        except Exception:
            raise mvc_exc.ItemNotStored(f"Can't update {name.items()} because it is not stored")

        for key, value in name.items():
            setattr(update_it, key, new_value)
            s.add(update_it)


def delete_items(table_name, **name):
    with session_scope() as s:
        keys = get_all_keys(table_name)
        for key, value in name.items():
            f = False

            for item in keys:
                if key == item:
                    f = True
                    d = getattr(table_name, key).type
                    if type(d) is Integer:
                        d = 0
                    elif type(d) is Boolean:
                        d = False
                    elif type(d) is Date:
                        d = DT.datetime.strptime('2020,1,1', '%Y,%m,%d').date()
                    elif type(d) is String:
                        d = 'str'
                    if type(d) != type(value):
                        raise mvc_exc.ValueTypeError(f"Value: <{value}> must be the same type as key!")

            if f is False:
                raise mvc_exc.KeyNameError(f"Key: <{key}> doesn't exist in table '{table_name.__tablename__}'!")

        try:
            delete_it = s.query(table_name).filter_by(**name).one()
        except Exception:
            raise mvc_exc.ItemNotStored(f"Can't delete {name.items()} because it is not stored")

        s.delete(delete_it)


def query1(conn, num, e_type, f_type):
    cur = conn.cursor()

    cur.execute(f"SELECT * FROM users as us INNER JOIN (SELECT * FROM email) as em ON us.user_id = em.user_id "
                f"INNER JOIN (SELECT * FROM folders) as fl ON em.email_id = fl.email_id "
                f"WHERE us.phone_number>{num} AND em.email_type LIKE '%{e_type}%' AND fl.folder_type LIKE '%{f_type}%' "
                f"ORDER BY us.user_id;")
    result = cur.fetchall()

    keys = [description[0] for description in cur.description]
    print(keys)

    if cur.rowcount == 0:
        print("[No such data]")

    for item in result:
        print(item)

    cur.close()


def query2(conn, e_num, m_range1, m_range2, mess_name):
    cur = conn.cursor()

    cur.execute(f"SELECT * FROM folders as fl INNER JOIN (SELECT * FROM folders_messages) as fm "
                f"ON fl.folders_id = fm.folders_id "
                f"INNER JOIN (SELECT * FROM messages) as ms ON ms.messages_id = fm.messages_id "
                f"WHERE fl.email_id < {e_num} AND (fm.messages_id > {m_range1} AND fm.messages_id < {m_range2}) AND "
                f"(ms.message_name LIKE '%{mess_name}%') "
                f"ORDER BY fl.folders_id ASC;")
    result = cur.fetchall()

    keys = [description[0] for description in cur.description]
    print(keys)

    if cur.rowcount == 0:
        print("[No such data]")

    for item in result:
        print(item)

    cur.close()


def query3(conn, username, usr_range, e_adress):
    cur = conn.cursor()

    cur.execute(f"SELECT * FROM users as us INNER JOIN (SELECT * FROM email) as em ON us.user_id = em.email_id "
                f"WHERE us.username LIKE '%{username}%' AND em.user_id > {usr_range} AND "
                f"em.email_adress LIKE '%{e_adress}%' "
                f"ORDER BY us.user_id;")
    result = cur.fetchall()

    keys = [description[0] for description in cur.description]
    print(keys)

    if cur.rowcount == 0:
        print("[No such data]")

    for item in result:
        print(item)

    cur.close()


def random_users(conn, rows):
    cur = conn.cursor()

    cur.execute("DELETE FROM users;")

    SQL = "INSERT INTO users (user_id, phone_number, username) VALUES (%s, %s, %s);"

    cur.execute("SELECT trunc(random()*(1000000) + 1)::int FROM generate_series(1,100010) ")
    rand_num = cur.fetchall()

    cur.execute("SELECT chr(trunc(65+random()*25)::int) || chr(trunc(65+random()*25)::int) "
                "FROM generate_series(1,100010)")
    rand_name = cur.fetchall()

    i = 1
    while i < rows:
        data = (i, rand_num[i], rand_name[i])
        cur.execute(SQL, data)
        i = i + 1

    cur.execute("SELECT * FROM users;")
    rows = cur.fetchall()
    print("========= USERS TABLE =========")
    print("ID|Username|Phone_Num")
    for row in rows:
        print(row)

    conn.commit()
    cur.close()


def random_email(conn, rows):
    cur = conn.cursor()

    cur.execute("DELETE FROM email;")

    SQL = "INSERT INTO email (email_id, user_id, email_adress, email_type) VALUES (%s, %s, %s, %s);"

    cur.execute("SELECT max(user_id) FROM users")
    usr_id_max = cur.fetchone()

    if (cur.rowcount == 0) or (usr_id_max is None):
        raise mvc_exc.ParentTabError(f"You can't create random data for email table if parent table doesn't exist")

    cur.execute(f"SELECT user_id FROM users")
    user_ids = cur.fetchall()
    cur.execute(f"SELECT trunc(random()*({usr_id_max[0]}-1) + 1) FROM generate_series(1,100010)")
    rand_id = cur.fetchall()

    i = 0
    for item in rand_id:
        f = False
        for keys in user_ids:
            if item == keys:
                f = True

        if f is False:
            rand_id[i] = usr_id_max[0]
        i = i + 1

    cur.execute("SELECT trunc(random()*(1000))::int ||"
                "chr(trunc(65+random()*25)::int) || chr(trunc(65+random()*25)::int)FROM generate_series(1,100010) ")
    rand_num = cur.fetchall()

    cur.execute("SELECT chr(trunc(65+random()*25)::int) || chr(trunc(65+random()*25)::int) "
                "FROM generate_series(1,100010)")
    rand_name = cur.fetchall()

    i = 1
    while i < rows:
        data = (i, rand_id[i], rand_num[i], rand_name[i])
        cur.execute(SQL, data)
        i = i + 1

    cur.execute("SELECT * FROM email;")
    rows = cur.fetchall()
    print("========= EMAIL TABLE =========")
    print("ID|U_ID|Adress|E_Type ")
    for row in rows:
        print(row)

    conn.commit()
    cur.close()


def random_folders(conn, rows):
    cur = conn.cursor()

    cur.execute("DELETE FROM folders;")

    SQL = "INSERT INTO folders (folders_id, email_id, folder_name, folder_type) VALUES (%s, %s, %s, %s);"

    cur.execute("SELECT max(email_id) FROM email")
    eml_id_max = cur.fetchone()

    cur.execute("SELECT email_id FROM email")
    eml_ids = cur.fetchall()

    if (cur.rowcount == 0) or (eml_id_max is None):
        raise mvc_exc.ParentTabError(f"You can't create random data for folders table if parent table doesn't exist")

    cur.execute(f"SELECT trunc(random()*({eml_id_max[0]}-1) + 1) FROM generate_series(1,100010)")
    rand_id = cur.fetchall()

    i = 0
    for item in rand_id:
        f = False
        for keys in eml_ids:
            if item == keys:
                f = True

        if f is False:
            rand_id[i] = eml_id_max[0]
        i = i + 1

    cur.execute("SELECT chr(trunc(65+random()*25)::int) || "
                "trunc(random()*(1000) + 1)::int || chr(trunc(65+random()*25)::int) FROM generate_series(1,100010) ")
    rand_name1 = cur.fetchall()

    cur.execute("SELECT chr(trunc(65+random()*25)::int) || chr(trunc(65+random()*25)::int) "
                "FROM generate_series(1,100010)")
    rand_name2 = cur.fetchall()

    i = 1
    while i < rows:
        data = (i, rand_id[i], rand_name1[i], rand_name2[i])
        cur.execute(SQL, data)
        i = i + 1

    cur.execute("SELECT * FROM folders;")
    rows = cur.fetchall()
    print("========= FOLDERS TABLE =========")
    print("ID|E_ID|F_Name|F_Type")
    for row in rows:
        print(row)

    conn.commit()
    cur.close()


def random_fm(conn, rows):
    cur = conn.cursor()

    cur.execute("DELETE FROM folders_messages;")

    SQL = "INSERT INTO folders_messages (folders_id, messages_id) VALUES (%s, %s);"

    cur.execute("SELECT max(messages_id) FROM messages")
    mes_id_max = cur.fetchone()

    cur.execute("SELECT messages_id FROM messages")
    mes_ids = cur.fetchall()

    cur.execute("SELECT max(folders_id) FROM folders")
    fold_id_max = cur.fetchone()

    cur.execute("SELECT folders_id FROM folders")
    fold_ids = cur.fetchall()

    if ((cur.rowcount == 0) or (mes_id_max is None)) or ((cur.rowcount == 0) or (fold_id_max is None)):
        raise mvc_exc.ParentTabError(f"You can't create random data for folders_messages table if parent table "
                                     f"doesn't exist")

    cur.execute(f"SELECT trunc(random()*({fold_id_max[0]}-1) + 1) FROM generate_series(1,100010)")
    rand_f_id = cur.fetchall()

    i = 0
    for item in rand_f_id:
        f = False
        for keys in fold_ids:
            if item == keys:
                f = True

        if f is False:
            rand_f_id[i] = fold_id_max[0]
        i = i + 1

    cur.execute(f"SELECT trunc(random()*({mes_id_max[0]}-1) + 1) FROM generate_series(1,100010)")
    rand_m_id = cur.fetchall()

    i = 0
    for item in rand_m_id:
        f = False
        for keys in mes_ids:
            if item == keys:
                f = True

        if f is False:
            rand_m_id[i] = mes_id_max[0]
        i = i + 1

    i = 1
    while i < rows:
        data = (rand_f_id[i], rand_m_id[i])
        cur.execute(SQL, data)
        i = i + 1

    cur.execute("SELECT * FROM folders_messages;")
    rows = cur.fetchall()
    print("========= FOLDERS_MESSAGES TABLE =========")
    print("FoldersID|Messages_ID")
    for row in rows:
        print(row)

    conn.commit()
    cur.close()


def random_messages(conn, rows):
    cur = conn.cursor()

    cur.execute("DELETE FROM messages;")

    SQL = "INSERT INTO messages (messages_id, read_or_not, message_name, message_date) VALUES (%s, %s, %s, %s);"

    cur.execute("SELECT bool(random() > 0.5) FROM generate_series(1,100010)")
    rand_bool = cur.fetchall()

    cur.execute("SELECT chr(trunc(65+random()*25)::int) || chr(trunc(65+random()*25)::int)"
                "|| chr(trunc(65+random()*25)::int) || chr(trunc(65+random()*25)::int) FROM generate_series(1,100010) ")
    rand_name = cur.fetchall()

    cur.execute("SELECT timestamp '2018-01-01 00:00:00' + random()*(timestamp '2020-01-01 00:00:00' "
                "- timestamp '2018-01-01 00:00:00') FROM generate_series(1,100010)")
    rand_date = cur.fetchall()

    i = 1
    while i < rows:
        data = (i, rand_bool[i], rand_name[i], rand_date[i])
        cur.execute(SQL, data)
        i = i + 1

    cur.execute("SELECT * FROM messages;")
    rows = cur.fetchall()
    print("========= MESSAGES TABLE =========")
    print("ID|ReadOrNot|Name | Date")
    for row in rows:
        print(row)

    conn.commit()
    cur.close()

