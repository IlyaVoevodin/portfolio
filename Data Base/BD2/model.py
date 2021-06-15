import basic_backend


class ModelBasic(object):

    def __init__(self, conn, *table_name):
        for item in table_name:
            basic_backend.get_all_keys(conn, item)
            basic_backend.read_items(conn, item)

    @staticmethod
    def table_check(conn, table_name):
        basic_backend.table_check(conn, table_name)

    @staticmethod
    def get_all_keys(conn, table_name):
        basic_backend.get_all_keys(conn, table_name)

    @staticmethod
    def create_item(conn, table_name, *items):
        basic_backend.create_item(conn, table_name, *items)

    @staticmethod
    def read_item(conn, table_name, **name):
        return basic_backend.read_item(conn, table_name, **name)

    @staticmethod
    def read_from_range(conn, key, a, b, table_name):
        return basic_backend.read_from_range(conn, key, a, b, table_name)

    @staticmethod
    def read_items(conn, table_name):
        return basic_backend.read_items(conn, table_name)

    @staticmethod
    def update_item(conn, table_name, new_value, **name):
        basic_backend.update_item(conn, table_name, new_value, **name)

    @staticmethod
    def delete_item(conn, table_name, **name):
        basic_backend.delete_items(conn, table_name, **name)

    @staticmethod
    def query1(conn, num, e_type, f_type):
        basic_backend.query1(conn, num, e_type, f_type)

    @staticmethod
    def query2(conn, e_num, m_range1, m_range2, mess_name):
        basic_backend.query2(conn, e_num, m_range1, m_range2, mess_name)

    @staticmethod
    def query3(conn, username, usr_range, e_adress):
        basic_backend.query3(conn, username, usr_range, e_adress)

    @staticmethod
    def random_users(conn, rows):
        basic_backend.random_users(conn, rows)

    @staticmethod
    def random_email(conn, rows):
        basic_backend.random_email(conn, rows)

    @staticmethod
    def random_folders(conn, rows):
        basic_backend.random_folders(conn, rows)

    @staticmethod
    def random_fm(conn, rows):
        basic_backend.random_fm(conn, rows)

    @staticmethod
    def random_messages(conn, rows):
        basic_backend.random_messages(conn, rows)
