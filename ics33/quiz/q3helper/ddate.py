from goody import irange, type_as_str

class Date:
    month_dict = {1:31, 2:28, 3:31, 4:30, 5:31, 6:30, 7:31, 8:31, 9:30, 10:31, 11:30, 12:31}

    @staticmethod
    def is_leap_year(year):
        return (year%4 == 0 and year%100 != 0) or year%400 == 0
    
    @staticmethod
    def days_in(year,month):
        return Date.month_dict[month] + (1 if month == 2 and Date.is_leap_year(year) else 0)

    def __init__(self,year,month,day):
        assert all(type(i)==int for i in [year,month,day]) and year>=0 and month in range(1,13) and day in range(1,Date.days_in(year,month)+1)
        self.year,self.month,self.day=year,month,day

    def __getitem__(self,*arg):
        map={'m':self.month,'y':self.year,'d':self.day}
        arg=arg[0] if type(arg[0])==tuple else arg
        if all(i in ('m','y','d') for i in arg):
            return tuple(map[i] for i in arg) if len(arg)>1 else map[arg[0]]
        else:
            raise IndexError

    def __repr__(self):
        return 'Date({},{},{})'.format(*self['y','m','d'])

    def __str__(self):
        return '{}/{}/{}'.format(*self['m','d','y'])

    def __len__(self):
        return 365*self.year+((((self.year-1)//100*24+(self.year-1)//400+((self.year-1)%100)//4)+1) if self.year>=1 else 0)+sum(Date.days_in(self.year,i) for i in range(1,self.month))+self.day-1
    

    def op_base(self,arg,op1,op2):
        if type(arg)!=int and type(self)!=type(arg):
            raise TypeError
        elif type(arg)==int:
            return op1(self,arg)
        else:
            return op2(self,arg)


    def __lt__(self,arg):
        return self.op_base(arg,lambda x,y:len(x)<y,lambda x,y:len(x)<len(y))
        

    def __add__(self,arg):
        if type(arg)!=int:
            raise TypeError
        result=Date(*self['y','m','d'])
        flag=1 if arg>0 else -1 
        while arg:
            if abs(arg)>365:
                if flag==1:
                    arg-=(365+(0 if ((result.month==2 and result.day==29) or result.month>2) else Date.is_leap_year(result.year)))
                else:
                    arg+=(365+(Date.is_leap_year(result.year)) if ((result.month==2 and result.day==29) or result.month>2) else 0)
                result.year+=1*flag
            elif abs(arg)>=Date.days_in(*result['y','m']):
                if flag==1:
                    arg-=Date.days_in(*result['y','m'])
                    result.month+=1
                    if result.month>12:
                        result.month=1
                        result.year+=1
                else:
                    result.month-=1
                    if result.month<1:
                        result.month=12
                        result.year-=1
                    arg+=Date.days_in(*result['y','m'])
            else:
                result.day+=arg
                if flag==1 and result.day>=Date.days_in(*result['y','m']):
                    result.day-=Date.days_in(*result['y','m'])
                    result.month+=1
                    if result.month>12:
                        result.month=1
                        result.year+=1
                elif result.day<1:
                    result.month-=1
                    if result.month<1:
                        result.month=12
                        result.year-=1
                    result.day+=Date.days_in(*result['y','m'])
                return result

    def __radd__(self,arg):
        return self+arg

    
    def __sub__(self,arg):
        return self.op_base(arg,lambda x,y:x+(-y),lambda x,y:len(x)-len(y))
        
    def __call__(self,year,month,day):
        self.__init__(year,month,day)
            
        
        



    
if __name__ == '__main__':
    # Put in simple tests for Date before allowing driver to run

    print()
    import driver
    
    driver.default_file_name = 'bsc1.txt'
#     driver.default_show_traceback = True
#     driver.default_show_exception = True
#     driver.default_show_exception_message = True
    driver.driver()



        
        
        
        
        
