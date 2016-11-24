#Shengquan Ni 46564157

ConsumerKey='eHxDVGhxYPZfoM6Ir2S4knVsy8PcBTiS'
ConsumerSecret='z1ooHHZ7TnOjeGWE'
Direction_URL='http://open.mapquestapi.com/directions/v2/route?'
Elevation_URL='http://open.mapquestapi.com/elevation/v1/profile?'

import json
import urllib.parse
import urllib.request


def build_URL(base_url,data):
    '''use base_url and data to build a full url''' 
    return base_url+urllib.parse.urlencode(data)

def Process_URL(inputs):
    ''' use MapQuest to process user's locations and recieve data, get latlngdata from previous data, then get elevation data
        return a tuple which has 3 elements, which includes full_data latlngdata and elevation data
        if any error occurs, it will return (None,None,None)
    '''
    print('Processing...\n')
    count=len(inputs)
    inputs=[i for i in zip(['from']+['to'for i in range(count-1)],inputs)]
    full_url=build_URL(Direction_URL,[('key',ConsumerKey)]+inputs)
    try:
        webresponse=urllib.request.urlopen(full_url)
    except:
        webresponse=None
    if webresponse and webresponse.getcode()==200 and webresponse.readable():
        data=json.loads(webresponse.read().decode())
        if data['route']['routeError']['errorCode']!=-400:
            print('NO ROUTE FOUND'+'\n')
            return None,None,None
        else:
            latlngdata=[(i['latLng']['lat'],i['latLng']['lng']) for i in data['route']['locations']]
            eledata=[]
            for i in range(count):
                elevation_url=build_URL(Elevation_URL,[('key',ConsumerKey),('latLngCollection',str(latlngdata[i][0])+','+str(latlngdata[i][1]))])
                eledata+=[json.loads(urllib.request.urlopen(elevation_url).read().decode())]
            return data,latlngdata,eledata
    else:
        print('MAPQUEST ERROR'+'\n')
        return None,None,None


'function of standardize one-line-user-input'
'''

I use it as a outside function, so it is not a part of this project.
Thus I don't want to write any docstring to the function.

P.S. check_core is a recursive function (there are lots of 'return's and 'check_core's inside),
every step of it takes part in the recursion. so I don't want to broke it apart.

author: Shengquan Ni 
date: 2/16/2016
purpose: check if user input accords of specific format
'''    
def check_core(types,args,sep):
    if not types:
        return []
    elif isinstance(types,dict):
        for i in types.keys():
            k=args.find(sep) if sep and args.find(sep)!= -1 else None
            tempres=check_core(i,args[:k],sep)
            if tempres:
                tempres2=check_core(types[i],args[k:].strip(),sep)
                if tempres2!=None:
                    return tempres+tempres2
                else:
                    return None
    elif isinstance(types,tuple):
        res=None
        for i in types:
            try:
                if res!=None:
                    if callable(i):
                        temp=i(res)
                    else:
                        return check_core(i,temp,sep)
                else:
                    k=args.find(sep) if sep and args.find(sep)!=-1 else None
                    if callable(i):
                        temp=i(args[:k])
                    else:
                        return check_core(i,args[:k],sep)
                if not isinstance(temp,bool):
                    res=temp
                elif not temp:
                    return None
                elif res==None:
                    res=args[:k]
            except:
                return None
        return [res]
    elif isinstance(types,list):
        result=[]
        for i in types:
            r=check_core(i,args,sep)
            if r!=None:
                result+=r
                args=args.split(sep,maxsplit=len(r))[-1]
            else:
                return None
        return result
    else:
        try:
            result=types(args)
            return [result] if not isinstance(result,bool) else args if result else None
        except:
            if types==args:
                return [args]
            elif types==args.upper():
                return [args.upper()]
            return None
            

def check_type(types,errormessage='ERROR',hint='',sep=' '):
    while True:
        args=input(hint)
        result=check_core(types,args,sep)
        if result!=None:
            if len(result)!=1:
                return result
            else:
                return result[0]
        print(errormessage)
