import mvc_exceptions as mvc_exc
import psycopg2
import datetime as DT


def table_check(conn, table_name):
    cur = conn.cursor()

    cur.execute("SELECT table_name FROM information_schema.tables WHERE table_schema='public'")
    table_names = cur.fetchall()

    f = False
    for item in table_names:
        if table_name == item[0]:
            f = True

    if f is False:
        raise mvc_exc.WrongInput(f"Table name '{table_name}' is incorrect")

    cur.close()


def get_all_keys(conn, table_name):
    cur = conn.cursor()

    cur.execute(f"SELECT * FROM {table_name}")
    keys = [description[0] for description in cur.description]
    print(keys)

    cur.close()


def create_item(conn, table_name, *value):
    cur = conn.cursor()

    cur.execute(f"SELECT column_name, data_type FROM information_schema.columns "
                f"WHERE table_schema='public' AND table_name = '{table_name}'")
    data_type = cur.fetchall()

    type_dat = []
    for item in data_type:
        type_dat += [item[1]]

    j = 0
    for item in type_dat:
        if type_dat[j] == 'integer':
            type_dat[j] = 1
        if type_dat[j] == 'boolean':
            type_dat[j] = False
        if type_dat[j] == 'date':
            type_dat[j] = DT.datetime.strptime('2020,1,1', '%Y,%m,%d').date()

        if type(type_dat[j]) != type(value[j]):
            raise mvc_exc.ValueTypeError(f"Type of value '{value[j]}' not the same as type of key name!")
        j = j + 1

    cur.execute(f"SELECT * FROM {table_name}")
    keys = [description[0] for description in cur.description]

    cur.execute(f"SELECT * FROM {table_name} WHERE {keys[0]} = {value[0]}")
    if cur.rowcount != 0:
        raise mvc_exc.ItemAlreadyStored(f'ID: "{value[0]}" already stored!')

    if table_name == 'users':
        cur.execute(f"SELECT * FROM {table_name} WHERE {keys[1]} = '{value[1]}' and {keys[2]} = {value[2]}")
        if cur.rowcount != 0:
            raise mvc_exc.ItemAlreadyStored(f'Item with that value "{value[1]}" "{value[2]}" already stored!')
    elif table_name == ('email' or 'folders'):
        cur.execute(f"SELECT * FROM {table_name} WHERE {keys[1]} = {value[1]} and {keys[2]} = '{value[2]}' "
                    f"and {keys[3]} = '{value[3]}'")
        if cur.rowcount != 0:
            raise mvc_exc.ItemAlreadyStored(f'Item with that value "{value[1]}" "{value[2]}" "{value[3]}"'
                                            f' already stored!')
    elif table_name == 'messages':
        cur.execute(f"SELECT * FROM {table_name} WHERE {keys[1]} = {value[1]} and {keys[2]} = '{value[2]}' and "
                    f"{keys[3]} = '{value[3]}'")
        if cur.rowcount != 0:
            raise mvc_exc.ItemAlreadyStored(f'Item with that value "{value[1]}" "{value[2]}" "{value[3]}"'
                                            f' already stored!')
    elif table_name == 'folders_messages':
        cur.execute(f"SELECT * FROM {table_name} WHERE {keys[0]} = {value[0]} and {keys[1]} = {value[1]}")
        if cur.rowcount != 0:
            raise mvc_exc.ItemAlreadyStored(f'Item with that value "{value[0]}" "{value[1]}" '
                                            f' already stored!')

    if table_name == ('email' or 'folders'):
        cur.execute(f"INSERT INTO {table_name} ({keys[0]},{keys[1]},{keys[2]},{keys[3]}) "
                    f"VALUES ({value[0]}, {value[1]}, '{value[2]}', '{value[3]}')")
    elif table_name == 'users':
        cur.execute(f"INSERT INTO {table_name} ({keys[0]},{keys[1]},{keys[2]}) "
                    f"VALUES ({value[0]}, '{value[1]}', {value[2]})")
    elif table_name == 'messages':
        cur.execute(f"INSERT INTO {table_name} ({keys[0]},{keys[1]},{keys[2]},{keys[3]}) "
                    f"VALUES ({value[0]}, {value[1]}, '{value[2]}', '{value[3]}')")
    elif table_name == 'folders_messages':
        cur.execute(f"INSERT INTO {table_name} ({keys[0]},{keys[1]}) "
                    f"VALUES ({value[0]}, {value[1]})")

    conn.commit()
    cur.close()


def read_item(conn, table_name, **name):
    cur = conn.cursor()

    cur.execute(f"SELECT column_name, data_type FROM information_schema.columns "
                f"WHERE table_schema='public' AND table_name = '{table_name}'")
    data_type = cur.fetchall()

    type_dat = []
    for item in data_type:
        type_dat += [item[1]]

    j = 0
    for item in type_dat:
        if type_dat[j] == 'integer':
            type_dat[j] = 1
        if type_dat[j] == 'boolean':
            type_dat[j] = False
        if type_dat[j] == 'date':
            type_dat[j] = DT.datetime.strptime('2020,1,1', '%Y,%m,%d').date()
        j = j + 1

    f = False
    for key, value in name.items():
        i = 0
        for item in data_type:
            if item[0] == key:
                f = True
                if type(type_dat[i]) != type(value):
                    raise mvc_exc.ValueTypeError(f"Type of argument {value} is not the same as key type")
            i = i + 1

        if f is False:
            raise mvc_exc.KeyNameError(f"Key name {key} doesn't exist")

        if type(value) is (int or bool):
            cur.execute(f"SELECT * FROM {table_name} as id WHERE id.{key}={value} ")
        else:
            cur.execute(f"SELECT * FROM {table_name} as id WHERE id.{key}='{value}' ")
        result = cur.fetchall()

        if cur.rowcount != 0:
            print("\nSearch result:")
            for row in result:
                print(row)
        else:
            raise mvc_exc.ItemNotStored(
                'Can\'t read "{}" because it\'s not stored'.format(name))

    cur.close()
    return [row for row in result]


def read_from_range(conn, key, a, b, table_name):
    cur = conn.cursor()

    cur.execute(f"SELECT column_name, data_type FROM information_schema.columns "
                f"WHERE table_schema='public' AND table_name = '{table_name}'")
    data_type = cur.fetchall()

    type_dat = []
    for item in data_type:
        type_dat += [item[1]]

    j = 0
    for item in type_dat:
        if type_dat[j] == 'integer':
            type_dat[j] = 1
        if type_dat[j] == 'boolean':
            type_dat[j] = False
        if type_dat[j] == 'date':
            type_dat[j] = DT.datetime.strptime('2020,1,1', '%Y,%m,%d').date()
        j = j + 1

    cur.execute(f"SELECT * FROM {table_name}")
    keys = [description[0] for description in cur.description]

    i = 0
    for ids in keys:
        if key == ids:
            if (type(data_type[i]) != type(a)) or (type(data_type[i]) != type(b)):
                raise mvc_exc.ValueTypeError(f"Key {key} and value {a} type not the same!")

            if (type(a) is int) and (type(b) is int):
                cur.execute(f"SELECT * FROM {table_name} WHERE ({key} > {a}) AND ({key} < {b}) ")
                result = cur.fetchall()
            elif type(a) is str:
                cur.execute(f"SELECT * FROM {table_name} WHERE {key} LIKE '%{a}%' ")
                result = cur.fetchall()
            elif type(a) is bool:
                cur.execute(f"SELECT * FROM {table_name} WHERE {key} = {a} ")
                result = cur.fetchall()
            else:
                cur.execute(f"SELECT * FROM {table_name} WHERE ({key} > '{a}') AND ({key} < '{b}') ")
                result = cur.fetchall()

    if cur.rowcount == 0:
        print(f"In table {table_name} no such objects")
    else:
        for rows in result:
            print(rows)

    cur.close()


def read_items(conn, *table_name):
    cur = conn.cursor()

    for items in table_name:
        cur.execute(f"SELECT * FROM {items};")
        rows = cur.fetchall()

        for row in rows:
            print(row)

    cur.close()


def update_item(conn, table_name, new_value, **name):
    cur = conn.cursor()

    cur.execute(f"SELECT column_name, data_type FROM information_schema.columns "
                f"WHERE table_schema='public' AND table_name = '{table_name}'")
    data_type = cur.fetchall()

    type_dat = []
    for item in data_type:
        type_dat += [item[1]]

    j = 0
    for item in type_dat:
        if type_dat[j] == 'integer':
            type_dat[j] = 1
        if type_dat[j] == 'boolean':
            type_dat[j] = False
        if type_dat[j] == 'date':
            type_dat[j] = DT.datetime.strptime('2020,1,1', '%Y,%m,%d').date()
        j = j + 1

    f = False
    for key, value, in name.items():
        i = 0
        for item in data_type:
            if item[0] == key:
                f = True
                if type(type_dat[i]) != type(value):
                    raise mvc_exc.ValueTypeError(f"Type of argument {value} is not the same as key type")
                if type(type_dat[i]) != type(new_value):
                    raise mvc_exc.ValueTypeError(f"Type of argument {new_value} is not the same as key type")
            i = i + 1

        if f is False:
            raise mvc_exc.KeyNameError(f"Key name {key} doesn't exist")

        if type(value) is (int or bool):
            cur.execute(f"SELECT * FROM {table_name} as id WHERE id.{key}={value} ")
            if cur.rowcount == 0:
                raise mvc_exc.ItemNotStored('Can\'t update "{}" because it\'s not stored'.format(name))
            else:
                cur.execute(f"UPDATE {table_name} set {key} = {new_value} WHERE {key} = {value} ")
        else:
            cur.execute(f"SELECT * FROM {table_name} as id WHERE id.{key}='{value}' ")
            if cur.rowcount == 0:
                raise mvc_exc.ItemNotStored('Can\'t update "{}" because it\'s not stored'.format(name))
            else:
                cur.execute(f"UPDATE {table_name} set {key} = '{new_value}' WHERE {key} = '{value}' ")

    conn.commit()
    cur.close()
    return conn


def delete_items(conn, table_name, **name):
    cur = conn.cursor()

    cur.execute(f"SELECT column_name, data_type FROM information_schema.columns "
                f"WHERE table_schema='public' AND table_name = '{table_name}'")
    data_type = cur.fetchall()

    type_dat = []
    for item in data_type:
        type_dat += [item[1]]

    j = 0
    for item in type_dat:
        if type_dat[j] == 'integer':
            type_dat[j] = 1
        if type_dat[j] == 'boolean':
            type_dat[j] = False
        if type_dat[j] == 'date':
            type_dat[j] = DT.datetime.strptime('2020,1,1', '%Y,%m,%d').date()
        j = j + 1

    f = False
    for key, value in name.items():
        i = 0
        for item in data_type:
            if item[0] == key:
                f = True
                if type(type_dat[i]) != type(value):
                    raise mvc_exc.ValueTypeError(f"Type of argument {value} is not the same as key type")
            i = i + 1

        if f is False:
            raise mvc_exc.KeyNameError(f"Key name {key} doesn't exist")

        if type(value) is (int or bool):
            cur.execute(f"SELECT * FROM {table_name} WHERE {key} = {value}")
            if cur.rowcount == 0:
                raise mvc_exc.ItemNotStored('Can\'t delete "{}" because it\'s not stored'.format(name))
            else:
                cur.execute(f"DELETE FROM {table_name} WHERE {key} = {value}")
        else:
            cur.execute(f"SELECT * FROM {table_name} WHERE {key} = '{value}'")
            if cur.rowcount == 0:
                raise mvc_exc.ItemNotStored('Can\'t delete "{}" because it\'s not stored'.format(name))
            else:
                cur.execute(f"DELETE FROM {table_name} WHERE {key} = '{value}'")

    conn.commit()
    cur.close()
    return conn


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

    cur.execute("SELECT trunc(random()*(1000000) + 1)::int FROM generate_series(1,1000) ")
    rand_num = cur.fetchall()

    cur.execute("SELECT chr(trunc(65+random()*25)::int) || chr(trunc(65+random()*25)::int) "
                "FROM generate_series(1,1000)")
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
    cur.execute(f"SELECT trunc(random()*({usr_id_max[0]}-1) + 1) FROM generate_series(1,1000)")
    rand_id = cur.fetchall()

    i = 0
    for item in rand_id:
        f = False
        for keys in user_ids:
            if item == keys:
                f = True

        if f is False:
            rand_id[i] = usr_id_max[0]
        i = i+1

    cur.execute("SELECT trunc(random()*(1000))::int ||"
                "chr(trunc(65+random()*25)::int) || chr(trunc(65+random()*25)::int)FROM generate_series(1,1000) ")
    rand_num = cur.fetchall()

    cur.execute("SELECT chr(trunc(65+random()*25)::int) || chr(trunc(65+random()*25)::int) "
                "FROM generate_series(1,1000)")
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

    cur.execute(f"SELECT trunc(random()*({eml_id_max[0]}-1) + 1) FROM generate_series(1,1000)")
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
                "trunc(random()*(1000) + 1)::int || chr(trunc(65+random()*25)::int) FROM generate_series(1,1000) ")
    rand_name1 = cur.fetchall()

    cur.execute("SELECT chr(trunc(65+random()*25)::int) || chr(trunc(65+random()*25)::int) "
                "FROM generate_series(1,1000)")
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

    cur.execute(f"SELECT trunc(random()*({fold_id_max[0]}-1) + 1) FROM generate_series(1,1000)")
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

    cur.execute(f"SELECT trunc(random()*({mes_id_max[0]}-1) + 1) FROM generate_series(1,1000)")
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

    cur.execute("SELECT bool(random() > 0.5) FROM generate_series(1,1000)")
    rand_bool = cur.fetchall()

    cur.execute("SELECT chr(trunc(65+random()*25)::int) || chr(trunc(65+random()*25)::int)"
                "|| chr(trunc(65+random()*25)::int) || chr(trunc(65+random()*25)::int) FROM generate_series(1,1000) ")
    rand_name = cur.fetchall()

    cur.execute("SELECT timestamp '2018-01-01 00:00:00' + random()*(timestamp '2020-01-01 00:00:00' "
                "- timestamp '2018-01-01 00:00:00') FROM generate_series(1,1000)")
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
