import psycopg2
from view import View
from model import ModelBasic
import mvc_exceptions as mvc_exc
import datetime as DT


class Controller(object):

    def __init__(self, model, view):
        self.model = model
        self.view = view

    def menu(self, conn):
        self.view.menu()

        try:
            mod = input()
            self.is_int(mod)
            mod = int(mod)
            self.range_check(mod, 0, 9)
        except mvc_exc.ValueNotInt as err:
            self.view.int_error(err)
            return 0
        except mvc_exc.RangeError as err:
            self.view.range_error(err)
            return 0

        try:
            if 0 < mod < 6:
                self.view.choose_table()

                table = input()
                self.model.table_check(conn, table)
                if mod != 2:
                    self.view.print_table(table)
                    self.model.get_all_keys(conn, table)
                    self.model.read_items(conn, table)
        except mvc_exc.WrongInput as err:
            self.view.wrong_input(err)
            return 0

        if mod == 1:
            self.view.show_read()
            print("Input key:")
            key = input()
            print("Input value:")
            value = input()

            f = False
            if (table == 'messages') and (key == 'message_date'):
                value = DT.datetime.strptime(value, '%Y,%m,%d').date()
                f = True

            if f is False:
                if value.isdigit() is True:
                    value = int(value)
                if self.is_bool(value) is True:
                    value = True
                if self.is_bool(value) is False:
                    value = False

            d = {key: value}

            try:
                self.model.read_item(conn, table, **d)
            except mvc_exc.ItemNotStored as err:
                self.view.item_not_stored(err, **d)
            except mvc_exc.KeyNameError as err:
                self.view.key_name_err(err)
            except mvc_exc.ValueTypeError as err:
                self.view.value_type_err(err)

        if mod == 2:
            self.view.show_all()
            self.view.print_table(table)
            self.model.get_all_keys(conn, table)
            self.model.read_items(conn, table)

        if mod == 3:
            self.view.show_create()
            self.model.get_all_keys(conn, table)

            data = []
            if table == 'users':
                data += [input(f"For key {i + 1} Value =") for i in range(0, 3, 1)]

                i = 0
                for item in data:
                    if item.isdigit() is True:
                        data[i] = int(data[i])
                    if self.is_bool(item) is True:
                        data[i] = True
                    if self.is_bool(item) is False:
                        data[i] = False
                    i = i+1

                try:
                    self.model.create_item(conn, table, data[0], data[1], data[2])
                    self.view.print_table(table)
                    self.model.get_all_keys(conn, table)
                    self.model.read_items(conn, table)
                except mvc_exc.ItemAlreadyStored as err:
                    self.view.item_stored(err)
                except mvc_exc.WrongInput as err:
                    self.view.wrong_input(err)
                except mvc_exc.ValueTypeError as err:
                    self.view.value_type_err(err)

            elif table == 'folders_messages':
                data += [input(f"For key {i + 1} Value =") for i in range(0, 2, 1)]

                for i in range(0, 2, 1):
                    try:
                        if self.is_int(data[i]) is True:
                            data[i] = int(data[i])
                    except mvc_exc.ValueNotInt as err:
                        self.view.int_error(err)

                try:
                    self.model.create_item(conn, table, data[0], data[1])
                    self.view.print_table(table)
                    self.model.get_all_keys(conn, table)
                    self.model.read_items(conn, table)
                except mvc_exc.ItemAlreadyStored as err:
                    self.view.item_stored(err)
                except mvc_exc.WrongInput as err:
                    self.view.wrong_input(err)
                except mvc_exc.ValueTypeError as err:
                    self.view.value_type_err(err)
            else:
                data += [input(f"For key {i + 1} Value =") for i in range(0, 4, 1)]

                i = 0
                for item in data:
                    f = False
                    if (table == 'messages') and (item == data[3]):
                        try:
                            data[i] = DT.datetime.strptime(data[i], '%Y,%m,%d').date()
                        except ValueError as err:
                            self.view.value_type_err(err)
                        f = True

                    if f is False:
                        if (data[i]).isdigit() is True:
                            data[i] = int(data[i])
                        if self.is_bool(data[i]) is True:
                            data[i] = True
                        if self.is_bool(data[i]) is False:
                            data[i] = False
                    i = i+1

                try:
                    self.model.create_item(conn, table, data[0], data[1], data[2], data[3])
                    self.view.print_table(table)
                    self.model.get_all_keys(conn, table)
                    self.model.read_items(conn, table)
                except mvc_exc.ItemAlreadyStored as err:
                    self.view.item_stored(err)
                except mvc_exc.WrongInput as err:
                    self.view.wrong_input(err)
                except mvc_exc.ValueTypeError as err:
                    self.view.value_type_err(err)

        if mod == 4:
            self.view.show_update()

            print("Input key:")
            key = input()
            print("Input value:")
            value = input()
            print("Input new value:")
            new_value = input()

            f = False
            if (table == 'messages') and (key == 'message_date'):
                value = DT.datetime.strptime(value, '%Y,%m,%d').date()
                new_value = DT.datetime.strptime(new_value, '%Y,%m,%d').date()
                f = True

            if f is False:
                if value.isdigit() is True:
                    value = int(value)
                if self.is_bool(value) is True:
                    value = True
                if self.is_bool(value) is False:
                    value = False

                if new_value.isdigit() is True:
                    new_value = int(new_value)
                if self.is_bool(new_value) is True:
                    new_value = True
                if self.is_bool(new_value) is False:
                    new_value = False

            d = {key: value}

            try:
                self.model.update_item(conn, table, new_value, **d)
            except mvc_exc.ItemNotStored as err:
                self.view.item_not_stored(err, **d)
                return 0
            except mvc_exc.KeyNameError as err:
                self.view.key_name_err(err)
                return 0
            except mvc_exc.ValueTypeError as err:
                self.view.value_type_err(err)
                return 0

            self.view.print_table(table)
            self.model.get_all_keys(conn, table)
            self.model.read_items(conn, table)

        if mod == 5:
            self.view.show_delete()
            print("Input key: ")
            key = input()
            print("Input value:")
            value = input()

            f = False
            if (table == 'messages') and (key == 'message_date'):
                value = DT.datetime.strptime(value, '%Y,%m,%d').date()
                f = True

            if f is False:
                if value.isdigit() is True:
                    value = int(value)
                if self.is_bool(value) is True:
                    value = True
                if self.is_bool(value) is False:
                    value = False

            d = {key: value}

            try:
                self.model.delete_item(conn, table, **d)
                self.view.print_table(table)
                self.model.get_all_keys(conn, table)
                self.model.read_items(conn, table)
            except mvc_exc.ItemNotStored as err:
                self.view.item_not_stored(err, **d)
            except mvc_exc.KeyNameError as err:
                self.view.key_name_err(err)
            except mvc_exc.ValueTypeError as err:
                self.view.value_type_err(err)

        if mod == 6:
            self.view.show_random()

            try:
                table = input()
                self.is_int(table)
                table = int(table)
                self.range_check(table, 0, 7)
            except mvc_exc.ValueNotInt as err:
                self.view.int_error(err)
            except mvc_exc.RangeError as err:
                self.view.range_error(err)

            print("Input rows number:")
            rows = input()

            try:
                self.is_int(rows)
                rows = int(rows)
                self.range_check(rows, 0, 100000)

                if table == 1:
                    self.model.random_users(conn, rows)
                if table == 2:
                    try:
                        self.model.random_email(conn, rows)
                    except mvc_exc.ParentTabError as err:
                        self.view.parent_tab_err(err)
                if table == 3:
                    try:
                        self.model.random_folders(conn, rows)
                    except mvc_exc.ParentTabError as err:
                        self.view.parent_tab_err(err)
                if table == 4:
                    self.model.random_messages(conn, rows)
                if table == 5:
                    try:
                        self.model.random_fm(conn, rows)
                    except mvc_exc.ParentTabError as err:
                        self.view.parent_tab_err(err)
                if table == 6:
                    try:
                        self.model.random_users(conn, rows)
                        self.model.random_email(conn, rows)
                        self.model.random_folders(conn, rows)
                        self.model.random_fm(conn, rows)
                        self.model.random_messages(conn, rows)
                    except mvc_exc.ParentTabError as err:
                        self.view.parent_tab_err(err)
            except mvc_exc.ValueNotInt as err:
                self.view.int_error(err)
            except mvc_exc.RangeError as err:
                self.view.range_error(err)

        if mod == 7:
            table = ['users', 'email', 'folders', 'messages']

            self.view.show_read_range()

            f = True
            j = 0
            date = DT.datetime.strptime('2020,1,1', '%Y,%m,%d').date()
            key, value1, value2 = [], [], []
            while f is True:
                print("Input key:")
                key += input()
                print("Input first value:")
                value1 += input()
                if type(value1[j]) == (int or type(date)):
                    print("Input second value:")
                    value2 += input()
                else:
                    value2 += (1,)

                fp = False
                if (table == 'messages') and (key[j] == 'message_date'):
                    value1[j] = DT.datetime.strptime(value1[j], '%Y,%m,%d').date()
                    value2[j] = DT.datetime.strptime(value2[j], '%Y,%m,%d').date()
                    fp = True

                if fp is False:
                    if (value1[j]).isdigit() is True:
                        value1[j] = int(value1[j])
                    if self.is_bool(value1[j]) is True:
                        value1[j] = True
                    if self.is_bool(value1[j]) is False:
                        value1[j] = False

                    if (value2[j]).isdigit() is True:
                        value2[j] = int(value2[j])
                    if self.is_bool(value2[j]) is True:
                        value2[j] = True
                    if self.is_bool(value2[j]) is False:
                        value2[j] = False

                self.view.go_or_stop()
                var = input()
                try:
                    f = self.choose(var)
                except mvc_exc.WrongInput as err:
                    self.view.wrong_input(err)

            for table_name in table:
                i = 0
                for item in key:
                    try:
                        self.model.read_from_range(conn, item, value1[i], value2[i], table_name)
                        self.view.print_table(table_name)
                        self.model.get_all_keys(conn, table_name)
                        self.model.read_items(conn, table_name)
                    except mvc_exc.ValueTypeError as err:
                        self.view.value_type_err(err)
                    except mvc_exc.KeyNameError as err:
                        self.view.key_name_err(err)
                    i = i + 1

        if mod == 8:
            self.view.select_query()
            var = input()

            try:
                self.is_int(var)
                var = int(var)
                self.range_check(var, 0, 4)
            except mvc_exc.RangeError as err:
                self.view.range_error(err)
            except mvc_exc.ValueNotInt as err:
                self.view.int_error(err)

            if var == 1:
                self.view.query1(100000, 'B', 'C')
                self.model.query1(conn, 100000, 'B', 'C')

                print("Input number range:")
                num = input()

                try:
                    self.is_int(num)
                    num = int(num)
                except mvc_exc.ValueNotInt as err:
                    self.view.int_error(err)

                print("Input email type:")
                e_type = input()
                print("Input folder type:")
                f_type = input()

                self.view.query1(num, e_type, f_type)
                self.model.query1(conn, num, e_type, f_type)

            if var == 2:
                self.view.query2(10, 2, 9, 'U')
                self.model.query2(conn, 10, 2, 9, 'U')

                print("Input email_id range:")
                e_num = input()
                try:
                    self.is_int(e_num)
                    e_num = int(e_num)
                except mvc_exc.ValueNotInt as err:
                    self.view.int_error(err)
                print("Input first value for message_id >'m1':")
                m_range1 = input()
                try:
                    self.is_int(m_range1)
                    m_range1 = int(m_range1)
                except mvc_exc.ValueNotInt as err:
                    self.view.int_error(err)
                print("Input second value for message_id <'m2':")
                m_range2 = input()
                try:
                    self.is_int(m_range2)
                    m_range2 = int(m_range2)
                except mvc_exc.ValueNotInt as err:
                    self.view.int_error(err)
                print("Input message name:")
                mess_name = input()

                self.view.query2(e_num, m_range1, m_range2, mess_name)
                self.model.query2(conn, e_num, m_range1, m_range2, mess_name)

            if var == 3:
                self.view.query3('A', 5, 'D')
                self.model.query3(conn, 'A', 5, 'D')

                print("Input username:")
                username = input()
                print("Input range for users_id:")
                usr_range = input()
                try:
                    self.is_int(usr_range)
                    usr_range = int(usr_range)
                except mvc_exc.ValueNotInt as err:
                    self.view.int_error(err)
                print("Input email_adress:")
                e_adress = input()

                self.view.query3(username, usr_range, e_adress)
                self.model.query3(conn, username, usr_range, e_adress)

    @staticmethod
    def is_int(value):
        if value.isdigit() is True:
            return True
        else:
            raise mvc_exc.ValueNotInt(f"{value}  is not integer!")

    @staticmethod
    def range_check(value, a, b):
        if a < value < b:
            return True
        else:
            raise mvc_exc.RangeError(f"{value} out of range ({a + 1},{b - 1})")

    @staticmethod
    def is_bool(value):
        if value == 'True':
            return True
        if value == 'False':
            return False

    @staticmethod
    def choose(yes_or_not):
        if yes_or_not == 'Y' or 'y':
            return True
        elif yes_or_not == 'N' or 'n':
            return False
        else:
            raise mvc_exc.WrongInput(f"Wrong input, {yes_or_not} is not Y(y) or N(n)")


def main():
    conn = psycopg2.connect("dbname=Email user=postgres password = qwerty")

    c = Controller(ModelBasic(conn, 'users', 'email', 'folders', 'messages'), View())

    c.menu(conn)

    conn.close()


if __name__ == '__main__':
    main()
