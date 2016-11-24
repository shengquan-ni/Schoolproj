import functools

meter_to_feet=3.2808399

class DataStore:
    ''' base class to store data'''
    def __init__(self,data,latlngdata,eledata):
        '''initialize'''
        self.data=data
        self.latlngdata=latlngdata
        self.eledata=eledata
        self.type=None
        self.result=None
    def PrintResult(self):
        '''print what type of the data is and what result it carrys'''
        if isinstance(self.result,list):
            print(self.type)
            for j in self.result:
                print(j)
            print()
        else:
            print(self.type+':'+self.result+'\n')


class GetSTEPS(DataStore):
    def Process(self):
        '''filtrate narrative steps from data '''
        self.type='DIRECTIONS'
        self.result=[k['narrative'] for k in functools.reduce(lambda x,y:x+y,[i['maneuvers'] for i in self.data['route']['legs']])]


class GetTOTALDISTANCE(DataStore):
    def Process(self):
        '''filtrate total distance from data '''
        self.type='TOTAL DISTANCE'
        self.result='{:} miles'.format(round(float(self.data['route']['distance'])))


class GetTOTALTIME(DataStore):
    def Process(self):
        '''filtrate total time from data '''
        self.type='TOTAL TIME'
        self.result='{:} minutes'.format(round(float(self.data['route']['time'])/60))

class GetLATLONG(DataStore):
    def Process(self):
        '''filtrate latitude and longitude and accurate to the second decimal place from latlngdata '''
        self.type='LATLONGS'
        self.result=['{} {}'.format('{:.2f}'.format(abs(j[0]))+('' if j[0]==0 or abs(j[0])==180 else 'N ' if j[0]>0 else 'S '),\
                                    '{:.2f}'.format(abs(j[1]))+('' if j[1]==0 or abs(j[1])==90 else 'E ' if j[1]>0 else 'W ')) for j in self.latlngdata]

class GetELEVATION(DataStore):
    def Process(self):
        '''filtrate elevation from eledata then transform to feet, round to integer '''
        self.type='ELEVATIONS'
        self.result=[]
        for data in self.eledata:
            self.result+=[round(float(i['height'])*meter_to_feet) for i in data['elevationProfile']] if data['info']['statuscode']==0 else 'MAPQUEST ERROR'
