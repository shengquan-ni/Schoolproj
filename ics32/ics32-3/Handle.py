from Classes import *
from APIprocess import *


def transform(l,data,latlngdata,eledata):
    '''
    transform data to different data filters
    return a list of data filters
    '''
    d={'STEPS':GetSTEPS(data,latlngdata,eledata),\
       'TOTALDISTANCE':GetTOTALDISTANCE(data,latlngdata,eledata),\
       'TOTALTIME':GetTOTALTIME(data,latlngdata,eledata),\
       'LATLONG':GetLATLONG(data,latlngdata,eledata),\
       'ELEVATION':GetELEVATION(data,latlngdata,eledata)}
    result=[]
    for i in l:
        result.append(d[i])
    return result
        


def handle():
    #get addresses from user
    locations=[]
    count=check_type((int,lambda x:x>=2))
    for i in range(count):
        locations+=[input()]
    #get outputs from user
    commands=[]
    count2=check_type((int,lambda x:x>=1))
    for i in range(count2):
        commands+=[check_type({'STEPS':None,'TOTALDISTANCE':None,'TOTALTIME':None,'LATLONG':None,'ELEVATION':None}\
                              ,errormessage="it should be one of STEPS,TOTALDISTANCE,TOTALTIME,LATLONG,ELEVATION")]
    #get data from MapQuest
    data,latlngdata,eledata=Process_URL(locations)
    #filter data and generate results
    if all([data,latlngdata,eledata]):
        datafilters=transform(commands,data,latlngdata,eledata)
        for i in datafilters:
            i.Process()
            i.PrintResult()
    
    print('Directions Courtesy of MapQuest; Map Data Copyright OpenStreetMap Contributors')

if __name__=='__main__':
    handle()
