from collections import defaultdict


class History:
    def __init__(self):
        self.history=defaultdict(list)

    
    def __getattr__(self,name):
        if name.split('_prev')[0] not in self.__dict__ or any(i!='' for i in name.split('_prev')[1:]):
            raise NameError
        index=len(self.history[name.split('_prev')[0]])-name.count('_prev')-1
        return self.history[name.split('_prev')[0]][index] if index>=0 else None


    def __getitem__(self,index):
        if index>0:
            raise IndexError
        return {i:(self.history[i][len(self.history[i])+index-1] if len(self.history[i])+index-1>=0 else None) for i in self.history}
            

    
    def __setattr__(self,name,value):
        if name.find('_prev')!=-1:
            raise NameError
        if 'history' in self.__dict__:
            self.history[name].append(value)
        self.__dict__[name] = value
    





if __name__ == '__main__':
    # Put in simple tests for History before allowing driver to run

    print()
    import driver
    
    driver.default_file_name = 'bsc2.txt'
#     driver.default_show_traceback = True
#     driver.default_show_exception = True
#     driver.default_show_exception_message = True
    driver.driver()
