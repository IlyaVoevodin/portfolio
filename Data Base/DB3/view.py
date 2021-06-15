
class View(object):

    @staticmethod
    def menu():
        print("-------| Menu |-------")
        print("1. Read 1 item\n"
              "2. Read table\n"
              "3. Create item\n"
              "4. Update item\n"
              "5. Delete item\n"
              "6. Input random data in tables\n"
              "7. SQL query\n\n"
              "Select option by number...")

    @staticmethod
    def choose_table():
        print("Choose table and input it's name:")
        print("< users >, < email >, < folders >, <folders_messages >, < messages >")

    @staticmethod
    def print_table(table_name, keys):
        print(f"====== {table_name} TABLE ======")
        print(keys)

    @staticmethod
    def show_read():
        print('Choose key and value for search:\n')

    @staticmethod
    def show_read_range():
        print("Input key and 2 values for range search:")

    @staticmethod
    def show_all():
        print('All values from table:')

    @staticmethod
    def show_create():
        print('Input your data for all keys to create item:\n')

    @staticmethod
    def show_update():
        print("Choose key and value to update:\n")

    @staticmethod
    def show_delete():
        print("Choose key and value to delete:\n")

    @staticmethod
    def show_random():
        print('Choose table or all tables:')
        print('1. "users"\n'
              '2. "email"\n'
              '3. "folders"\n'
              '4. "messages"\n'
              '5. "folders_messages"\n'
              '6. All tables\n'
              'Input number to select...')

    @staticmethod
    def select_query():
        print("Choose query:\n"
              "1.Query1(users + email + folders)\n"
              "2.Query2(folders + folders_messages + messages)\n"
              "3.Query3(users + email)\n"
              "Input number to select...")

    @staticmethod
    def wrong_input(err):
        print("Wrong input, try again!")
        print(f"{err.args[0]}")

    @staticmethod
    def item_not_stored(err, **item):
        for key, value in item.items():
            print(f"Table doesn't have {key}={value}")
        print(f"{err.args[0]}")

    @staticmethod
    def int_error(err):
        print("Value must be integer!")
        print(f"{err.args[0]}")

    @staticmethod
    def item_stored(err):
        print("Value error, item already exists")
        print(f"{err.args[0]}")

    @staticmethod
    def key_name_err(err):
        print("Key name error")
        print(f"{err.args[0]}")

    @staticmethod
    def value_type_err(err):
        print("Value type error")
        print(f"{err.args[0]}")

    @staticmethod
    def range_error(err):
        print("Range error")
        print(f"{err.args[0]}")

    @staticmethod
    def parent_tab_err(err):
        print("Parent table error")
        print(f"{err.args[0]}")

    @staticmethod
    def query1(num, e_type, f_type):
        print(f"SELECT script where phone_number>{num}, email_type with '{e_type}' in it "
              f"and folder_type with '{f_type}' in it")

    @staticmethod
    def query2(e_num, m_range1, m_range2, mess_name):
        print(f"SELECT script where email_id < {e_num}, {m_range1} < messages_id < {m_range2} and "
              f"messages_name with '{mess_name}' in it")

    @staticmethod
    def query3(username, usr_range, e_adress):
        print(f"SELECT script where username have '{username}' in it, user_id in email >{usr_range} "
              f"and email_adress have '{e_adress}' in it")


