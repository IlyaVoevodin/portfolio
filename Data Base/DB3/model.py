import basic_backend


class ModelBasic(object):

    def __init__(self, *table_name):
        for table in table_name:
            print(basic_backend.get_all_keys(table))
            basic_backend.read_items(table)

    @staticmethod
    def session_scope():
        return basic_backend.session_scope()

    @staticmethod
    def table_check(table_name):
        return basic_backend.table_check(table_name)

    @staticmethod
    def get_all_keys(table_name):
        return basic_backend.get_all_keys(table_name)

    @staticmethod
    def create_item(table_name, *items):
        return basic_backend.create_item(table_name, *items)

    @staticmethod
    def read_item(table_name, **name):
        return basic_backend.read_item(table_name, **name)

    @staticmethod
    def read_items(table_name):
        return basic_backend.read_items(table_name)

    @staticmethod
    def update_item(table_name, new_value, **name):
        return basic_backend.update_item(table_name, new_value, **name)

    @staticmethod
    def delete_item(table_name, **name):
        return basic_backend.delete_items(table_name, **name)

    @staticmethod
    def query1(conn, num, e_type, f_type):
        return basic_backend.query1(conn, num, e_type, f_type)

    @staticmethod
    def query2(conn, e_num, m_range1, m_range2, mess_name):
        return basic_backend.query2(conn, e_num, m_range1, m_range2, mess_name)

    @staticmethod
    def query3(conn, username, usr_range, e_adress):
        return basic_backend.query3(conn, username, usr_range, e_adress)

    @staticmethod
    def random_users(conn, rows):
        return basic_backend.random_users(conn, rows)

    @staticmethod
    def random_email(conn, rows):
        return basic_backend.random_email(conn, rows)

    @staticmethod
    def random_folders(conn, rows):
        return basic_backend.random_folders(conn, rows)

    @staticmethod
    def random_fm(conn, rows):
        return basic_backend.random_fm(conn, rows)

    @staticmethod
    def random_messages(conn, rows):
        return basic_backend.random_messages(conn, rows)
