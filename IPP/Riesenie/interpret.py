#
# IPP projekt 2
# Richard Filo(xfilor00)
# interpret.py
#

import sys, getopt, re
import xml.etree.ElementTree as ET

source_file = None
input_file = None

def error_exit(err_code):
    error_msg = {
        10 : "chybejici parametr skriptu nebo pouziti zakazane kombinace parametru",
        11 : "chyba pri otevirani vstupnich souboru",
        12 : "chyba pri otevreni vystupnich souboru pro zapis",
        31 : "chybny XML format ve vstupnim souboru",
        32 : "neocekavana struktura XML ci lexikalni nebo syntakticka chyba textovych elementu a atributu ve vstupnim XML souboru",
        52 : "chyba pri semantickych kontrolach vstupniho kodu v IPPcode21",
        53 : "behova chyba interpretace – špatne typy operandu",
        54 : "behova chyba interpretace – pristup k neexistujici promenne",
        55 : "behova chyba interpretace – ramec neexistuje",
        56 : "behova chyba interpretace – chybejici hodnota",
        57 : "behova chyba interpretace – špatna hodnota operandu",
        58 : "behova chyba interpretace – chybna prace s retezcem",
        99 : "interni chyba"
    }
    print("CHYBA:", error_msg[err_code], file=sys.stderr)
    exit(err_code)

def usage(out):
    print("""
    Skript nacte XML reprezentaci programu a tento programs vyuzitim
    vstupu dle parametru prikazove radky interpretuje a generuje vystup.

    Prepinace:
    --help - vypise napovedu skriptu
    --source=file - vstupni soubor s XML reprezentaci zdrojoveho kodu 
    --input=file - soubor se vstupy pro samotnou interpretaci zadaneho zdrojoveho kodu

    Alespon jeden z parametru (--source nebo --input) musi byt vzdy zadan. Pokud jeden z nich
    chybi, jsou chybejici data nacitana ze standardniho vstupu.
    """, file=out)

def parse_args():
    global source_file, input_file
    try:
        opts, args = getopt.getopt(sys.argv[1:], "", ["help", "source=", "input="])
    except getopt.GetoptError :
        usage(sys.stderr)
        error_exit(10)

    if len(opts) < 1:
        usage(sys.stderr)
        error_exit(10)

    for o, a in opts:
        if o == "--help" and len(opts) == 1:
            usage(sys.stdout)
            sys.exit()
        elif o == "--source":
            source_file = a
        elif o == "--input":
            input_file = a
        else:
            usage(sys.stderr)
            error_exit(10)

    if source_file == None:
        source_file = sys.stdin
    else:
        try:
            source_file = open(source_file, "r")
        except IOError:
            error_exit(11)

    if input_file == None:
        input_file = sys.stdin
    else:
        try:
            input_file = open(input_file, "r")
        except IOError:
            error_exit(11)


class Xml_parser():
    def __init__(self):
        try:
            self.root = ET.parse(source_file).getroot()
        except Exception:
            error_exit(31)
        self.order_list = []

    def check_format(self):
        if self.root.tag == 'program' and 'language' in self.root.attrib and self.root.attrib['language'] == 'IPPcode21':
            for atr in self.root.attrib:
                if atr not in ['language', 'name', 'description']:
                    print("Nepovoleny atribut v korenovom elemente program!", file=sys.stderr)
                    error_exit(32)
        
            def check_label(arg):
                if not ( arg is not None and len(arg.attrib) == 1 and 'type' in arg.attrib and arg.attrib['type'] == 'label' and arg.text and re.match(r"^(\_|\-|\$|\&|\%|\*|\!|[a-zA-Z])(\_|\-|\$|\&|\%|\*|\!|[a-zA-Z0-9])*$", arg.text)):
                    print("Nepovoleny format argumentu instrukce!", file=sys.stderr)
                    error_exit(32)

            def check_var(arg):
                if not ( arg is not None and len(arg.attrib) == 1 and 'type' in arg.attrib and arg.attrib['type'] == 'var' and arg.text and re.match(r"^(GF|LF|TF)@(\_|\-|\$|\&|\%|\*|\!|[a-zA-Z])(\_|\-|\$|\&|\%|\*|\!|[a-zA-Z0-9])*$", arg.text)):
                    print("Nepovoleny format argumentu instrukce!", file=sys.stderr)
                    error_exit(32)

            def check_type(arg):
                if not ( arg is not None and len(arg.attrib) == 1 and 'type' in arg.attrib and arg.attrib['type'] == 'type' and arg.text and re.match(r"^(int|bool|string|nil)$", arg.text)):
                    print("Nepovoleny format argumentu instrukce!", file=sys.stderr)
                    error_exit(32)
            
            def check_symb(arg):
                if  arg is not None and len(arg.attrib) == 1 and 'type' in arg.attrib and arg.attrib['type'] in ['var', 'int', 'bool', 'string', 'nil']:
                    if arg.attrib['type'] == 'var':
                        check_var(arg)
                    elif arg.attrib['type'] == 'int':
                        if not arg.text or not re.match(r"^([+-]?[1-9][0-9]*|[+-]?[0-9])$", arg.text):
                            print("Nepovoleny format argumentu typu int!", file=sys.stderr)
                            error_exit(32)
                    elif arg.attrib['type'] == 'bool':
                        if not arg.text or not re.match(r"^(true|false)$", arg.text):
                            print("Nepovoleny format argumentu typu bool!", file=sys.stderr)
                            error_exit(32)
                    elif arg.attrib['type'] == 'string':
                        if arg.text is None:
                            arg.text = ''
                        else:
                            arg.text = re.sub(r"\\([0-9]{3})", lambda x: chr(int(x.group(1))), arg.text)
                    else:
                        if arg.text != 'nil':
                            print("Nepovoleny format argumentu typu nil!", file=sys.stderr)
                            error_exit(32)
                        
                else:
                    print("Nepovoleny format argumentu instrukce!", file=sys.stderr)
                    error_exit(32)

            
            for ins in self.root:
                if ins.tag == 'instruction' and len(ins.attrib) == 2 and 'opcode' in ins.attrib and 'order' in ins.attrib:
                    self.order_list.append(int(ins.attrib['order']))

                    if ins.attrib['opcode'].upper() in ['CREATEFRAME', 'PUSHFRAME', 'POPFRAME', 'RETURN', 'BREAK']: # nic
                        if len(ins) != 0:
                            print("Instrukcia \"{}\" s poradim {} ma nespravny pocet argumentov!".format(ins.attrib['opcode'],ins.attrib['order']), file=sys.stderr)
                            error_exit(32)
                    
                    elif  ins.attrib['opcode'].upper() in ['DEFVAR', 'POPS']:   # <var>
                        if len(ins) == 1:
                            check_var(ins.find('arg1'))
                        else:
                            print("Instrukcia \"{}\" s poradim {} ma nespravny pocet argumentov!".format(ins.attrib['opcode'],ins.attrib['order']), file=sys.stderr)
                            error_exit(32)
                    
                    elif  ins.attrib['opcode'].upper() in ['CALL', 'LABEL', 'JUMP']:    # <label>
                        if len(ins) == 1:
                            check_label(ins.find('arg1'))
                        else:
                            print("Instrukcia \"{}\" s poradim {} ma nespravny pocet argumentov!".format(ins.attrib['opcode'],ins.attrib['order']), file=sys.stderr)
                            error_exit(32)
                    
                    elif  ins.attrib['opcode'].upper() in ['PUSHS', 'WRITE', 'EXIT', 'DPRINT']: # <symb>
                        if len(ins) == 1:
                            check_symb(ins.find('arg1'))
                        else:
                            print("Instrukcia \"{}\" s poradim {} ma nespravny pocet argumentov!".format(ins.attrib['opcode'],ins.attrib['order']), file=sys.stderr)
                            error_exit(32)
                    
                    elif  ins.attrib['opcode'].upper() == 'READ':   # <var> <type>
                        if len(ins) == 2:
                            check_var(ins.find('arg1'))
                            check_type(ins.find('arg2'))
                        else:
                            print("Instrukcia \"{}\" s poradim {} ma nespravny pocet argumentov!".format(ins.attrib['opcode'],ins.attrib['order']), file=sys.stderr)
                            error_exit(32)
                    
                    elif  ins.attrib['opcode'].upper() in ['MOVE', 'NOT', 'INT2CHAR', 'STRLEN', 'TYPE']:    # <var> <symb>
                        if len(ins) == 2:
                            check_var(ins.find('arg1'))
                            check_symb(ins.find('arg2'))
                        else:
                            print("Instrukcia \"{}\" s poradim {} ma nespravny pocet argumentov!".format(ins.attrib['opcode'],ins.attrib['order']), file=sys.stderr)
                            error_exit(32)
                    
                    elif  ins.attrib['opcode'].upper() in ['JUMPIFEQ', 'JUMPIFNEQ']:    # <label> <symb1> <symb2>
                        if len(ins) == 3:
                            check_label(ins.find('arg1'))
                            check_symb(ins.find('arg2'))
                            check_symb(ins.find('arg3'))
                        else:
                            print("Instrukcia \"{}\" s poradim {} ma nespravny pocet argumentov!".format(ins.attrib['opcode'],ins.attrib['order']), file=sys.stderr)
                            error_exit(32)
                    
                    elif  ins.attrib['opcode'].upper() in ['ADD', 'SUB', 'MUL', 'IDIV', 'LT', 'GT', 'EQ', 'AND', 'OR', 'STRI2INT', 'CONCAT', 'GETCHAR', 'SETCHAR']: # <var> <symb1> <symb2>
                        if len(ins) == 3:
                            check_var(ins.find('arg1'))
                            check_symb(ins.find('arg2'))
                            check_symb(ins.find('arg3'))
                        else:
                            print("Instrukcia \"{}\" s poradim {} ma nespravny pocet argumentov!".format(ins.attrib['opcode'],ins.attrib['order']), file=sys.stderr)
                            error_exit(32)
                    
                    else:
                        print("Neznamy operacni kod instrukce \""+ins.attrib['opcode']+"\"!", file=sys.stderr)
                        error_exit(32)

                else:
                    print("Nepovoleny format instrukce!", file=sys.stderr)
                    error_exit(32)

            self.order_list.sort()
            prev = 0
            for order in self.order_list:
                if order <= prev:
                    print("Nevhodne poradie instrukcii!", file=sys.stderr)
                    error_exit(32)
                prev = order

        else:
            print("Nepovoleny format korenoveho elementu!", file=sys.stderr)
            error_exit(32)


class Labels():
    def __init__(self):
        self.call_stack = []
        self.labels = {}

    def push_order(self, order):
        self.call_stack.append(order)

    def pop_order(self):
        if len(self.call_stack) > 0:
            return self.call_stack.pop()
        else:
            error_exit(56)

    def get_order(self, label):
        if label in self.labels:
            return self.labels[label]
        else:
            error_exit(52)

    def add_label(self, label, order):
        if label in self.labels:
            if self.labels[label] != order:
                error_exit(52)
        else:
            self.labels[label] = order

class Data_stack():
    def __init__(self):
        self.stack = []

    def push_value(self, _value, _type):
        self.stack.append((_value, _type))

    def pop_value(self):
        if len(self.stack) > 0:
            return self.stack.pop()
        else:
            error_exit(56)

class Frames():
    def __init__(self):
        self.GF = {}
        self.LF = []
        self.TF = None

    def get_frame(self, frame):
        if frame == 'GF':
            return self.GF
        elif frame == 'LF':
            if len(self.LF) > 0:
                self.TF = self.LF[-1]
            else:
                error_exit(55)
        else:
            if self.TF is not None:
                return self.TF
            else:
                error_exit(55)

    def create_frame(self):
        self.TF = {}

    def push_frame(self):
        if self.TF is not None:
            self.LF.append(self.TF)
            self.TF = None
        else:
            error_exit(55)

    def pop_frame(self):
        if len(self.LF) > 0:
            self.TF = self.LF.pop()
        else:
            error_exit(55)

    def def_var(self, var):
        frame = var.split('@')[0]
        name = var.split('@')[1]

        frame = self.get_frame(frame)
        if name in frame:
            error_exit(52)
        else:
            frame[name] = None

    def get_var(self, var):
        frame = var.split('@')[0]
        name = var.split('@')[1]

        frame = self.get_frame(frame)
        if name in frame:
            if frame[name] is not None:
                return frame[name]['value'], frame[name]['type']
            else:
                error_exit(56)
        else:
            error_exit(54)

    def get_var_type(self, var):
        frame = var.split('@')[0]
        name = var.split('@')[1]

        frame = self.get_frame(frame)
        if name in frame:
            if frame[name] is not None:
                return frame[name]['type']
            else:
                return ""
        else:
            error_exit(54)

    def set_var(self, var, _value, _type):
        frame = var.split('@')[0]
        name = var.split('@')[1]

        frame = self.get_frame(frame)
        if name in frame:
            frame[name] = {'value':_value, 'type':_type}
        else:
            error_exit(54)

class Program_interpret():
    def __init__(self, xml):
        self.frames = Frames()
        self.data_stack = Data_stack()
        self.labels = Labels()
        self.program_counter = 0
        self.order_list = xml.order_list
        self.program = xml.root

    def find_label(self):
        ins = self.program.find(".//instruction[@order='{}']".format(self.order_list[self.program_counter]))
        opcode = ins.attrib['opcode'].upper()

        if opcode == 'LABEL':
            self.labels.add_label(ins.find('arg1').text, self.program_counter)

    def init_labels(self):
        while(self.program_counter < len(self.order_list)):
            self.find_label()
            self.program_counter += 1

        self.program_counter = 0

    def make_ins(self):
        ins = self.program.find(".//instruction[@order='{}']".format(self.order_list[self.program_counter]))
        opcode = ins.attrib['opcode'].upper()
        # print(self.program_counter, opcode)

        def get_symb(symb):
            if symb.attrib['type'] == 'var':
                return self.frames.get_var(symb.text)
            else:
                return symb.text, symb.attrib['type']

        def get_symb_type(symb):
            if symb.attrib['type'] == 'var':
                return self.frames.get_var_type(symb.text)
            else:
                return symb.attrib['type']

        if opcode == 'MOVE':
            _value, _type = get_symb(ins.find('arg2'))
            self.frames.set_var(ins.find('arg1').text, _value, _type)

        elif opcode == 'CREATEFRAME':
            self.frames.create_frame()
        
        elif opcode == 'PUSHFRAME':
            self.frames.push_frame()

        elif opcode == 'POPFRAME':
            self.frames.pop_frame()

        elif opcode == 'DEFVAR':
            self.frames.def_var(ins.find('arg1').text)

        elif opcode == 'CALL':
            self.labels.push_order(self.program_counter)
            self.program_counter = self.labels.get_order(ins.find('arg1').text)

        elif opcode == 'RETURN':
            self.program_counter = self.labels.pop_order()

        elif opcode == 'PUSHS':
            _value, _type = get_symb(ins.find('arg1'))
            self.data_stack.push_value(_value, _type)

        elif opcode == 'POPS':
            _value, _type = self.data_stack.pop_value()
            self.frames.set_var(ins.find('arg1').text, _value, _type)

        elif opcode in ['ADD', 'SUB', 'MUL', 'IDIV']:
            _value1, _type1 = get_symb(ins.find('arg2'))
            _value2, _type2 = get_symb(ins.find('arg3'))
            if _type1 == 'int' and _type2 == 'int':
                if opcode == 'ADD':
                    self.frames.set_var(ins.find('arg1').text, str(int(_value1) + int(_value2)), 'int')
                elif opcode == 'SUB':
                    self.frames.set_var(ins.find('arg1').text, str(int(_value1) - int(_value2)), 'int')
                elif opcode == 'MUL':
                    self.frames.set_var(ins.find('arg1').text, str(int(_value1) * int(_value2)), 'int')
                else:
                    if int(_value2) == 0:
                        error_exit(57)
                    self.frames.set_var(ins.find('arg1').text, str(int(_value1) // int(_value2)), 'int')
            else:
                error_exit(53)

        elif opcode == 'LT':
            _value1, _type1 = get_symb(ins.find('arg2'))
            _value2, _type2 = get_symb(ins.find('arg3'))
            if _type1 in ['int', 'string', 'bool'] and _type2 in ['int', 'string', 'bool'] and _type1 == _type2:
                if _type1 == 'int':
                    self.frames.set_var(ins.find('arg1').text, str(int(_value1) < int(_value2)).lower(), 'bool')
                elif _type1 == 'string':
                    self.frames.set_var(ins.find('arg1').text, str(_value1 < _value2).lower(), 'bool')
                else:
                    # str(bool(_value1.replace("false", "")) < bool(_value2.replace("false", ""))).lower()
                    self.frames.set_var(ins.find('arg1').text, str(_value1 < _value2).lower(), 'bool')
            else:
                error_exit(53)

        elif opcode == 'GT':
            _value1, _type1 = get_symb(ins.find('arg2'))
            _value2, _type2 = get_symb(ins.find('arg3'))
            if _type1 in ['int', 'string', 'bool'] and _type2 in ['int', 'string', 'bool'] and _type1 == _type2:
                if _type1 == 'int':
                    self.frames.set_var(ins.find('arg1').text, str(int(_value1) > int(_value2)).lower(), 'bool')
                elif _type1 == 'string':
                    self.frames.set_var(ins.find('arg1').text, str(_value1 > _value2).lower(), 'bool')
                else:
                    # str(bool(_value1.replace("false", "")) > bool(_value2.replace("false", ""))).lower()
                    self.frames.set_var(ins.find('arg1').text, str(_value1 > _value2).lower(), 'bool')
            else:
                error_exit(53)

        elif opcode == 'EQ':
            _value1, _type1 = get_symb(ins.find('arg2'))
            _value2, _type2 = get_symb(ins.find('arg3'))
            if _type1 in ['int', 'string', 'bool'] and _type2 in ['int', 'string', 'bool'] and _type1 == _type2:
                if _type1 == 'int':
                    self.frames.set_var(ins.find('arg1').text, str(int(_value1) == int(_value2)).lower(), 'bool')
                elif _type1 == 'string':
                    self.frames.set_var(ins.find('arg1').text, str(_value1 == _value2).lower(), 'bool')
                else:
                    # str(bool(_value1.replace("false", "")) == bool(_value2.replace("false", ""))).lower()
                    self.frames.set_var(ins.find('arg1').text, str(_value1 == _value2).lower(), 'bool')

            elif _type1 == 'nil' or _type2 == 'nil':
                if _type1 == _type2:
                    self.frames.set_var(ins.find('arg1').text, 'true', 'bool')
                else:
                    self.frames.set_var(ins.find('arg1').text, 'false', 'bool')
            else:
                error_exit(53)

        elif opcode == 'AND':
            _value1, _type1 = get_symb(ins.find('arg2'))
            _value2, _type2 = get_symb(ins.find('arg3'))
            if _type1 == 'bool' and _type2 == 'bool':
                if _value1 == 'true' and _value2 == 'true':
                    self.frames.set_var(ins.find('arg1').text, 'true', 'bool')
                else:
                    self.frames.set_var(ins.find('arg1').text, 'false', 'bool')
            else:
                error_exit(53)

        elif opcode == 'OR':
            _value1, _type1 = get_symb(ins.find('arg2'))
            _value2, _type2 = get_symb(ins.find('arg3'))
            if _type1 == 'bool' and _type2 == 'bool':
                if _value1 == 'false' and _value2 == 'false':
                    self.frames.set_var(ins.find('arg1').text, 'false', 'bool')
                else:
                    self.frames.set_var(ins.find('arg1').text, 'true', 'bool')
            else:
                error_exit(53)

        elif opcode == 'NOT':
            _value, _type = get_symb(ins.find('arg2'))
            if _type == 'bool':
                if _value == 'false':
                    self.frames.set_var(ins.find('arg1').text, 'true', 'bool')
                else:
                    self.frames.set_var(ins.find('arg1').text, 'false', 'bool')
            else:
                error_exit(53)

        elif opcode == 'INT2CHAR':
            _value, _type = get_symb(ins.find('arg2'))
            if _type == 'int':
                try:
                    char = chr(int(_value))
                except ValueError:
                    error_exit(58)

                self.frames.set_var(ins.find('arg1').text, char, 'string')

            else:
                error_exit(53)

        elif opcode == 'STRI2INT':
            _value1, _type1 = get_symb(ins.find('arg2'))
            _value2, _type2 = get_symb(ins.find('arg3'))
            if _type1 == 'string' and _type2 == 'int':
                if 0 <= int(_value2) < len(_value1):
                    self.frames.set_var(ins.find('arg1').text, str(ord(_value1[int(_value2)])), 'int')
                else:
                    error_exit(58)
            else:
                error_exit(53)

        elif opcode == 'READ':
            value = input_file.readline().split("\n")[0]    
            if ins.find('arg2').text in ['int', 'string', 'bool']:
                if value == "":
                    self.frames.set_var(ins.find('arg1').text, 'nil', 'nil')
                else:
                    if ins.find('arg2').text == 'int':
                        try:
                            self.frames.set_var(ins.find('arg1').text, int(value), 'int')
                        except ValueError:
                            self.frames.set_var(ins.find('arg1').text, 'nil', 'nil')

                    elif ins.find('arg2').text == 'string':
                        self.frames.set_var(ins.find('arg1').text, value, 'string')
                    else:
                        if value.upper() == 'TRUE':
                            self.frames.set_var(ins.find('arg1').text, 'true', 'bool')
                        else:
                            self.frames.set_var(ins.find('arg1').text, 'false', 'bool')
            else:
                error_exit(53)

        elif opcode == 'WRITE':
            _value, _type = get_symb(ins.find('arg1'))
            if _type == 'nil':
                print('', end='')
            else:
                print(_value, end='')

        elif opcode == 'CONCAT':
            _value1, _type1 = get_symb(ins.find('arg2'))
            _value2, _type2 = get_symb(ins.find('arg3'))
            if _type1 == 'string' and _type2 == 'string':
                    self.frames.set_var(ins.find('arg1').text, _value1 + _value2, 'string')
            else:
                error_exit(53)

        elif opcode == 'STRLEN':
            _value, _type = get_symb(ins.find('arg2'))
            if _type == 'string':
                self.frames.set_var(ins.find('arg1').text, str(len(_value)), 'int')
            else:
                error_exit(53)

        elif opcode == 'GETCHAR':
            _value1, _type1 = get_symb(ins.find('arg2'))
            _value2, _type2 = get_symb(ins.find('arg3'))
            if _type1 == 'string' and _type2 == 'int':
                if 0 <= int(_value2) < len(_value1):
                    self.frames.set_var(ins.find('arg1').text, _value1[int(_value2)], 'string')
                else:
                    error_exit(58)
            else:
                error_exit(53)

        elif opcode == 'SETCHAR':
            _value1, _type1 = self.frames.get_var(ins.find('arg1').text)
            _value2, _type2 = get_symb(ins.find('arg2'))
            _value3, _type3 = get_symb(ins.find('arg3'))

            if _type1 == 'string' and _type2 == 'int' and _type3 == 'string':
                if 0 <= int(_value2) < len(_value1) and len(_value3) > 0:
                    _value1 = list(_value1)
                    _value1[int(_value2)] = _value3[0]
                    _value1 = "".join(_value1)
                    self.frames.set_var(ins.find('arg1').text, _value1, 'string')
                else:
                    error_exit(58)
            else:
                error_exit(53)

        elif opcode == 'TYPE':
            _type = get_symb_type(ins.find('arg2'))
            self.frames.set_var(ins.find('arg1').text, _type, 'string')

        elif opcode == 'JUMP':
            self.program_counter = self.labels.get_order(ins.find('arg1').text)

        elif opcode == 'JUMPIFEQ':
            order = self.labels.get_order(ins.find('arg1').text)
            _value1, _type1 = get_symb(ins.find('arg2'))
            _value2, _type2 = get_symb(ins.find('arg3'))
            if _type1 == _type2:
                if _value1 == _value2:
                    self.program_counter = order
            elif _type1 == 'nil' or _type2 == 'nil':
                ...
            else:
                error_exit(53)

        elif opcode == 'JUMPIFNEQ':
            order = self.labels.get_order(ins.find('arg1').text)
            _value1, _type1 = get_symb(ins.find('arg2'))
            _value2, _type2 = get_symb(ins.find('arg3'))
            if _type1 == _type2:
                if _value1 != _value2:
                    self.program_counter = order
            elif _type1 == 'nil' or _type2 == 'nil':
                self.program_counter = order
            else:
                error_exit(53)

        elif opcode == 'EXIT':
            _value, _type = get_symb(ins.find('arg1'))
            if _type == 'int':
                if int(_value) < 0 or int(_value) > 49:
                    error_exit(57)
                exit(int(_value))
            else:
                error_exit(53)
        
        elif opcode == 'DPRINT':
            _value, _type = get_symb(ins.find('arg1'))
            print("Hodnota =", _value,"typ =", _type, file=sys.stderr)

        elif opcode == 'BREAK':
            print("Program counter =", self.program_counter, file=sys.stderr)
            print("GF =", self.frames.GF, file=sys.stderr)
            print("LF =", self.frames.LF, file=sys.stderr)
            print("TF =", self.frames.TF, file=sys.stderr)
            print("Data stack =", self.data_stack.stack, file=sys.stderr, end="\n\n")

    def interpret_code(self):
        self.init_labels()
        while(self.program_counter < len(self.order_list)):
            self.make_ins()
            self.program_counter += 1

parse_args() #parsovanie argumentov

xml = Xml_parser() 
xml.check_format()  #kontrola xml formatu a taktiez lexikalna a syntakticka kontrola

interpret = Program_interpret(xml)
interpret.interpret_code()  #interpretacia kodu