#Shengquan Ni 46564157 and Erqiang Guo 58813913

from collections import namedtuple

Reservation=namedtuple('Reservation','ID arrive depart guest')

from datetime import date
import copy



def P(argu=''):
    if not isinstance(argu,list):
        if not isinstance(argu,str):
            argu=str(argu)
        if "\n" in argu:
            argu=argu.replace("\n","\n    ")
        print("    "+argu)
    else:
        P_list(argu) if len(argu)!=0 else print("    empty list")
    
def P_list(list):
    for i in list:
        P(i)



def get_date_str(arrstr,depstr):
     return ([int(i.strip()) for i in arrstr.split('/')],[int(i.strip()) for i in depstr.split('/')])

def get_dates(arrlist,deplist):
     return (date(arrlist[2],arrlist[0],arrlist[1]),date(deplist[2],deplist[0],deplist[1]))

def SAFE_write(file,str):
     if file:
          file.write(str)


def separate_reservation(beds,start,end):
     temp1=[[start,end]]
     temp2=[]
     count=0
     flag=False
     for k,v in beds.items():
          flag=True
          temp3=[]
          templist=sorted(v,key=lambda x:cmpRL(x.arrive))
          while count<len(temp1):
               for i in range(len(templist)):
                    arr,dep=get_dates(*get_date_str(templist[i].arrive,templist[i].depart))
                    if temp1[count][0]<arr and temp1[count][1]>dep and temp1[count][0]<dep and temp1[count][1]>arr:
                         if i==len(templist)-1:
                              temp2+=[[k,dep,temp1[count][1]]]
                              temp2+=[[k,temp1[count][0],arr]]
                              temp3+=[[arr,dep]]
                              break
                         else:
                              temp2+=[[k,temp1[count][0],arr]]
                              temp3+=[[arr,dep]]
                              temp1[count:count+1]=[[dep,temp1[count][1]]]
                    elif temp1[count][0]<dep and temp1[count][1]<=dep and temp1[count][0]<arr and temp1[count][1]>arr:
                         temp2+=[[k,temp1[count][0],arr]]
                         temp3+=[[arr,temp1[count][1]]]
                         break
                    elif temp1[count][0]>=arr and temp1[count][1]>arr and temp1[count][0]<dep and temp1[count][1]<=dep:
                         temp3+=[temp1[count]]
                         break
                    elif temp1[count][0]>=arr and temp1[count][1]>arr and temp1[count][0]<dep and temp1[count][1]>dep:
                         temp3+=[[temp1[count][0],dep]]
                         temp1[count:count+1]=[[dep,temp1[count][1]]]
                    elif temp1[count][1]<=arr:
                         temp2+=[[k,temp1[count][0],temp1[count][1]]]
                         break
               count+=1    
          temp1+=temp3
          if len(temp3):
               flag=False
     if flag:
          return temp2
     else:
          return None
                                                     
               
def Room_select(room,start,end):
     for i in room:
          arr2,dep2=get_dates(*get_date_str(i.arrive,i.depart))
          if start<dep2 and end>arr2:
               return False
     return True
                      


def cmpRL(x):
     arrives=[int(i.strip()) for i in x.split('/')]
     arr=date(arrives[2],arrives[0],arrives[1])
     return arr


count_for_reservation=0
rescount=0
Beds={}


def Anteater_Bed_and_Breakfast(infile,outfile):
    global count_for_reservation,rescount,Beds
    if infile:
         for line in infile:
             command=line.strip()[:2].upper()
             text=line.strip()[2:].strip()
             if command=='NB':
                 if Beds.get(text)!=None:
                     SAFE_write(outfile,"Sorry, can't add room {:} again; it's already on the list.\n".format(text))
                 else:
                     Beds[text]=[]
             elif command=='LB':
                 SAFE_write(outfile,'Number of bedrooms in service:  {:}\n'.format(len(Beds)))
                 SAFE_write(outfile,'------------------------------------\n')
                 for k in sorted(Beds.keys(),key=lambda x:int(x)):
                     SAFE_write(outfile,k+'\n')
             elif command=='PL':
                 SAFE_write(outfile,text+'\n')
             elif command=='BD':
                 flag=True
                 for k,v in Beds.items():
                     if k==text:
                         del Beds[k]
                         flag=False
                         break
                 if flag:
                     SAFE_write(outfile,"Sorry, can't delete room {:}; it is not in service now\n".format(text))
             elif command=='NR':
                 text=text.split(maxsplit=3)
                 if text[0] in Beds:
                     arr,dep=get_dates(*get_date_str(text[1],text[2]))
                     if arr>=dep:
                         SAFE_write(outfile,"Sorry, can't reserve room {:} ({:} to {:});\n    ".format(text[0],text[1],text[2])+("can't leave before you arrive.\n" if arr>dep else "can't arrive and leave on the same day.\n"))
                     else:
                         flag=False
                         if Beds.get(text[0]):
                             for j in Beds[text[0]]:
                                  arr2,dep2=get_dates(*get_date_str(j.arrive,j.depart))
                                  if arr<dep2 and dep>arr2:
                                      flag=True
                                      break
                         if flag is False:
                             count_for_reservation+=1
                             rescount+=1
                             Beds[text[0]].append(Reservation(count_for_reservation,text[1],text[2],text[3]))
                             SAFE_write(outfile,'Reserving room {:} for {:} -- Confirmation #{:}\n    (arriving {:}, departing {:})\n'.format(text[0],text[3],count_for_reservation,text[1],text[2]))
                         else:
                             flag2=False
                             key2=0
                             for k,v in Beds.items():
                                  flag2=Room_select(v,arr,dep)
                                  if flag2:
                                       key2=k
                                       break
                             if flag2:
                                  count_for_reservation+=1
                                  rescount+=1
                                  Beds[key2].append(Reservation(count_for_reservation,text[1],text[2],text[3]))
                                  SAFE_write(outfile,'Reserving room {:} (move to {:}) for {:} -- Confirmation #{:}\n    (arriving {:}, departing {:})\n'.format(text[0],key2,text[3],count_for_reservation,text[1],text[2]))
                             else:
                                  #several rooms reversation
                                  sep=separate_reservation(Beds,arr,dep)
                                  if sep:
                                       for i in sep:
                                            count_for_reservation+=1
                                            rescount+=1
                                            res=Reservation(count_for_reservation,'{:2d}/{:2d}/{:4d}'.format(*[int(c) for c in i[1].strftime('%m/%d/%Y').split('/')]),'{:2d}/{:2d}/{:4d}'.format(*[int(c) for c in i[2].strftime('%m/%d/%Y').split('/')]),text[3])
                                            Beds[i[0]].append(res)
                                            SAFE_write(outfile,'Reserving room {:}  for {:} -- Confirmation #{:}\n    (arriving {:}, departing {:})\n'.format(i[0],text[3],res.ID,res.arrive,res.depart))
                                  else:
                                       SAFE_write(outfile,"Sorry, can't reserve room {:} ({:} to {:})\n".format(text[0],text[1],text[2]))     
                 else:
                     SAFE_write(outfile,"Sorry; can't reserve room {:}; room not in service\n".format(text[0]))
             elif command=='LR':
                 SAFE_write(outfile,'Number of reservations:  {:}\nNo. Rm. Arrive      Depart     Guest\n------------------------------------------------\n'.format(rescount))
                 '''
                 for i in range(count_for_reservation):
                     for k,v in Beds.items():
                         for j in v:
                             if j.ID==i+1:
                                 arrives=j.arrive.split('/')
                                 departs=j.depart.split('/')
                                 SAFE_write(outfile,'{:3d} {:} {:2d}/{:2d}/{:4d} {:2d}/{:2d}/{:4d} {:20s}\n'.format(i+1,k,int(arrives[0]),int(arrives[1]),int(arrives[2]),int(departs[0]),int(departs[1]),int(departs[2]),j.guest))
                 '''
                 result=[]
                 for k,v in Beds.items():
                     for i in v:
                          result.append([k,i])
                 for j in sorted(result,key=lambda x:cmpRL(x[1].arrive)):
                     arrives,departs=get_date_str(j[1].arrive,j[1].depart)
                     SAFE_write(outfile,'{:3d} {:} {:2d}/{:2d}/{:4d} {:2d}/{:2d}/{:4d} {:20s}\n'.format(*[j[1].ID,j[0],*arrives,*departs,j[1].guest]))
             elif command=='RR':
                 flag=False
                 num=int(text)
                 for k,v in Beds.items():
                     for i in range(len(v)):
                         if v[i].ID==num:
                             del v[i]
                             rescount-=1
                             flag=True
                             break
                     if flag:
                         break
                 if not flag:
                     SAFE_write(outfile,"Sorry, can't cancel reservation; no confirmation number {:}\n".format(text))
             elif command=='RB':
                 flag=False
                 for i in Beds.keys():
                     if i==text:
                         rescount-=len(Beds[i])
                         for j in Beds[i]:
                             SAFE_write(outfile,"Deleting room {:} forces cancellation of this reservation:\n   {:} arriving {:} and departing {:} (Conf. #{:})\n".format(text,j.guest,j.arrive,j.depart,j.ID))
                         del Beds[i]
                         flag=True
                         break
                 if not flag:
                     SAFE_write(outfile,"Sorry, can't delete room {:}; it is not in service now\n".format(text))
             elif command=='RD':
                 flag=True
                 for k,v in Beds.items():
                     for j in v:
                         if j.ID==int(text):
                             flag=False
                             del Beds[k]
                             rescount-=1
                             break
                     if flag is False:
                         break 
                 if flag:
                     SAFE_write(outfile,"Sorry, can't cancel reservation; no confirmation number {:}\n".format(text))
             elif command=='BR':
                 if Beds.get(text):
                     SAFE_write(outfile,'Reservations for room {:}:\n'.format(text))
                     for i in Beds[text]:
                         arrives,departs=get_date_str(i.arrive,i.depart)
                         SAFE_write(outfile,'   {:2d}/{:2d}/{:4d} to {:2d}/{:2d}/{:4d}:  {:}\n'.format(*[*arrives,*departs,i.guest]))
                 else:
                     SAFE_write(outfile,"Sorry, can't search room {:}; it is not in service now\n".format(text))
             elif command=='RG':
                 SAFE_write(outfile,'Reservations for {:}:\n'.format(text))
                 for k,v in Beds.items():
                     for i in v:
                         if i.guest==text:
                             arrives,departs=get_date_str(i.arrive,i.depart)
                             SAFE_write(outfile,'   {:2d}/{:2d}/{:4d} to {:2d}/{:2d}/{:4d}:   room {:}\n'.format(*[*arrives,*departs,k]))
             elif command=='LA':
                 SAFE_write(outfile,'Guests arriving on {:}:\n'.format(text))
                 for k,v in Beds.items():
                     for i in v:
                         if i.arrive==text:
                             SAFE_write(outfile,'   {:} (room {:})\n'.format(i.guest,k))
             elif command=='LD':
                 SAFE_write(outfile,'Guests departing on {:}:\n'.format(text))
                 for k,v in Beds.items():
                     for i in v:
                         if i.depart==text:
                             SAFE_write(outfile,'   {:} (room {:})\n'.format(i.guest,k))
             elif command=='LF':
                 dates=text.split()
                 arr,dep=get_dates(*get_date_str(dates[0],dates[1]))
                 SAFE_write(outfile,'Bedrooms free between {:} to {:}:\n'.format(dates[0],dates[1]))
                 for k,v in Beds.items():
                     flag=False
                     for j in v:
                         arr2,dep2=get_dates(*get_date_str(j.arrive,j.depart))
                         if arr<dep2 and dep>arr2:
                             flag=True
                             break
                     if flag is False:
                         SAFE_write(outfile,'   {:}\n'.format(k))
             elif command=='LO':
                 dates=text.split()
                 arr,dep=get_dates(*get_date_str(dates[0],dates[1]))
                 SAFE_write(outfile,'Bedrooms free between {:} to {:}:\n'.format(dates[0],dates[1]))
                 for k,v in Beds.items():
                     flag=True
                     for j in v:
                         arr2,dep2=get_dates(*get_date_str(j.arrive,j.depart))
                         if arr<dep2 and dep>arr2:
                             flag=False
                             break
                     if flag is False:
                         SAFE_write(outfile,'   {:}\n'.format(k))
         if outfile:
              savefile=open('save.txt','w')
              for i in Beds.keys():
                  savefile.write('NB {:}\n'.format(i))
              for k,v in Beds.items():
                  for j in v:
                      arrives,departs=get_date_str(j.arrive,j.depart)
                      savefile.write('NR {:} {:d}/{:d}/{:d} {:d}/{:d}/{:d} {:}\n'.format(*[k,*arrives,*departs,j.guest]))
              savefile.close()
              outfile.close()
         infile.close()

try:
     savefile=open('save.txt')
except:
     savefile=None
Anteater_Bed_and_Breakfast(savefile,None)
infile=open(input('What to input '))
outfile=open(input('What to output '),'w')
Anteater_Bed_and_Breakfast(infile,outfile)



'---------------------------------------------------------'
'Here is the console version of Anteater_Bed_and_Breakfast'
'---------------------------------------------------------'

def CONSOLE_Anteater_Bed_and_Breakfast():
    helptext=\
    '''
Please use one of these commands below:
NB (for "add a new bedroom") followed by an integer room number (in the range 1–999). Add a new bedroom with the specified room number.
LB (for "list bedrooms"). Print a list of the bedrooms currently available. 
PL (for "print line"), followed by any text. Simply print (or "echo") a line, 
## Comment, followed by any text.
NR (followed by a bedroom number, then an arrival date in the form mm/dd/yyyy, then a departure date in the form mm/dd/yyyy, then the guest's name): Add a new reservation for the specified room on the specified dates.
LR (for "list reservations"). Print all the reservations.
RR (for "remove reservation"), followed by the confirmation number of a reservation. Deletes the specified reservation.
BR (for "bedroom reservations"), followed by a number. Lists all reservations for a given bedroom.
RG (for "reservations by guest"), followed by a string. List all reservations for a given guest.
LA (for "list arrivals"), followed by a date in the same mm/dd/yyyy form as before. Print a list of all guests arriving on the specified date.
LD (for "list departures"), followed by a date in the same mm/dd/yy form as before. Print a list of all guests departing on the specified date.
LF (for "list free bedrooms"), followed by two dates. List all bedrooms that are free each night for a guest arriving on the first date and departing on the second.
LO (for "list occupied bedrooms"), followed by two dates. List all bedrooms that are occupied for at least one night between the given arrival and departure dates.
QU just quit the program
    '''
    global count_for_reservation,rescount,Beds
    print(helptext)
    while True:
         line=input()
         command=line.strip()[:2].upper()
         text=line.strip()[2:].strip()
         if command=='NB':
             if Beds.get(text)!=None:
                 print("Sorry, can't add room {:} again; it's already on the list.\n".format(text),end='')
             else:
                 Beds[text]=[]
         elif command=='LB':
             print('Number of bedrooms in service:  {:}\n'.format(len(Beds)),end='')
             print('------------------------------------')
             for k in sorted(Beds.keys(),key=lambda x:int(x)):
                 print(k)
         elif command=='PL':
             print(text)
         elif command=='BD':
             flag=True
             for k,v in Beds.items():
                 if k==text:
                     del Beds[k]
                     flag=False
                     break
             if flag:
                 print("Sorry, can't delete room {:}; it is not in service now\n".format(text),end='')
         elif command=='NR':
             text=text.split(maxsplit=3)
             if text[0] in Beds:
                 arr,dep=get_dates(*get_date_str(text[1],text[2]))
                 if arr>=dep:
                     print("Sorry, can't reserve room {:} ({:} to {:});\n    ".format(text[0],text[1],text[2])+("can't leave before you arrive.\n" if arr>dep else "can't arrive and leave on the same day.\n"),end='')
                 else:
                     flag=False
                     if Beds.get(text[0]):
                         for j in Beds[text[0]]:
                              arr2,dep2=get_dates(*get_date_str(j.arrive,j.depart))
                              if arr<dep2 and dep>arr2:
                                  flag=True
                                  break
                     if flag is False:
                         count_for_reservation+=1
                         rescount+=1
                         Beds[text[0]].append(Reservation(count_for_reservation,text[1],text[2],text[3]))
                         print('Reserving room {:} for {:} -- Confirmation #{:}\n    (arriving {:}, departing {:})\n'.format(text[0],text[3],count_for_reservation,text[1],text[2]),end='')
                     else:
                         flag2=False
                         key2=0
                         for k,v in Beds.items():
                              flag2=Room_select(v,arr,dep)
                              if flag2:
                                   key2=k
                                   break
                         if flag2:
                              count_for_reservation+=1
                              rescount+=1
                              Beds[key2].append(Reservation(count_for_reservation,text[1],text[2],text[3]))
                              print('Reserving room {:} (move to {:}) for {:} -- Confirmation #{:}\n    (arriving {:}, departing {:})\n'.format(text[0],key2,text[3],count_for_reservation,text[1],text[2]),end='')
                         else:
                              #several rooms reversation
                              sep=separate_reservation(Beds,arr,dep)
                              if sep:
                                   for i in sep:
                                        count_for_reservation+=1
                                        rescount+=1
                                        res=Reservation(count_for_reservation,'{:2d}/{:2d}/{:4d}'.format(*[int(c) for c in i[1].strftime('%m/%d/%Y').split('/')]),'{:2d}/{:2d}/{:4d}'.format(*[int(c) for c in i[2].strftime('%m/%d/%Y').split('/')]),text[3])
                                        Beds[i[0]].append(res)
                                        print('Reserving room {:}  for {:} -- Confirmation #{:}\n    (arriving {:}, departing {:})\n'.format(i[0],text[3],res.ID,res.arrive,res.depart),end='')
                              else:
                                   print("Sorry, can't reserve room {:} ({:} to {:})\n".format(text[0],text[1],text[2]),end='')     
             else:
                 print("Sorry; can't reserve room {:}; room not in service\n".format(text[0]),end='')
         elif command=='LR':
             print('Number of reservations:  {:}\nNo. Rm. Arrive      Depart     Guest\n------------------------------------------------\n'.format(rescount),end='')
             result=[]
             for k,v in Beds.items():
                 for i in v:
                      result.append([k,i])
             for j in sorted(result,key=lambda x:cmpRL(x[1].arrive)):
                 arrives,departs=get_date_str(j[1].arrive,j[1].depart)
                 print('{:3d} {:} {:2d}/{:2d}/{:4d} {:2d}/{:2d}/{:4d} {:20s}\n'.format(*[j[1].ID,j[0],*arrives,*departs,j[1].guest]),end='')
         elif command=='RR':
             flag=False
             num=int(text)
             for k,v in Beds.items():
                 for i in range(len(v)):
                     if v[i].ID==num:
                         del v[i]
                         rescount-=1
                         flag=True
                         break
                 if flag:
                     break
             if not flag:
                 print("Sorry, can't cancel reservation; no confirmation number {:}\n".format(text),end='')
         elif command=='RB':
             flag=False
             for i in Beds.keys():
                 if i==text:
                     rescount-=len(Beds[i])
                     for j in Beds[i]:
                         print("Deleting room {:} forces cancellation of this reservation:\n   {:} arriving {:} and departing {:} (Conf. #{:})\n".format(text,j.guest,j.arrive,j.depart,j.ID),end='')
                     del Beds[i]
                     flag=True
                     break
             if not flag:
                 print("Sorry, can't delete room {:}; it is not in service now\n".format(text),end='')
         elif command=='RD':
             flag=True
             for k,v in Beds.items():
                 for j in v:
                     if j.ID==int(text):
                         flag=False
                         del Beds[k]
                         rescount-=1
                         break
                 if flag is False:
                     break 
             if flag:
                 print("Sorry, can't cancel reservation; no confirmation number {:}\n".format(text),end='')
         elif command=='BR':
             if Beds.get(text):
                 print('Reservations for room {:}:\n'.format(text),end='')
                 for i in Beds[text]:
                     arrives,departs=get_date_str(i.arrive,i.depart)
                     print('   {:2d}/{:2d}/{:4d} to {:2d}/{:2d}/{:4d}:  {:}\n'.format(*[*arrives,*departs,i.guest]),end='')
             else:
                 print("Sorry, can't search room {:}; it is not in service now\n".format(text),end='')
         elif command=='RG':
             print('Reservations for {:}:\n'.format(text),end='')
             for k,v in Beds.items():
                 for i in v:
                     if i.guest==text:
                         arrives,departs=get_date_str(i.arrive,i.depart)
                         print('   {:2d}/{:2d}/{:4d} to {:2d}/{:2d}/{:4d}:   room {:}\n'.format(*[*arrives,*departs,k]),end='')
         elif command=='LA':
             print('Guests arriving on {:}:\n'.format(text),end='')
             for k,v in Beds.items():
                 for i in v:
                     if i.arrive==text:
                          print('   {:} (room {:})\n'.format(i.guest,k),end='')
         elif command=='LD':
             print('Guests departing on {:}:\n'.format(text),end='')
             for k,v in Beds.items():
                 for i in v:
                     if i.depart==text:
                         print('   {:} (room {:})\n'.format(i.guest,k),end='')
         elif command=='LF':
             dates=text.split()
             arr,dep=get_dates(*get_date_str(dates[0],dates[1]))
             print('Bedrooms free between {:} to {:}:\n'.format(dates[0],dates[1]),end='')
             for k,v in Beds.items():
                 flag=False
                 for j in v:
                     arr2,dep2=get_dates(*get_date_str(j.arrive,j.depart))
                     if arr<dep2 and dep>arr2:
                         flag=True
                         break
                 if flag is False:
                     print('   {:}\n'.format(k),end='')
         elif command=='LO':
             dates=text.split()
             arr,dep=get_dates(*get_date_str(dates[0],dates[1]))
             print('Bedrooms free between {:} to {:}:\n'.format(dates[0],dates[1]),end='')
             for k,v in Beds.items():
                 flag=True
                 for j in v:
                     arr2,dep2=get_dates(*get_date_str(j.arrive,j.depart))
                     if arr<dep2 and dep>arr2:
                         flag=False
                         break
                 if flag is False:
                     print('   {:}\n'.format(k),end='')
         elif command=='QU':
             break
         elif command=='##':
             pass
         else:
             print("'{:}' is not a vaild command, please check the command again".format(command))
    print('saving....')
    savefile=open('save.txt','w')
    for i in Beds.keys():
        savefile.write('NB {:}\n'.format(i))
    for k,v in Beds.items():
        for j in v:
            arrives,departs=get_date_str(j.arrive,j.depart)
            savefile.write('NR {:} {:d}/{:d}/{:d} {:d}/{:d}/{:d} {:}\n'.format(*[k,*arrives,*departs,j.guest]))
    savefile.close()
    print('saving complete')
    print('thanks for using the console version of this program!')
             




CONSOLE_Anteater_Bed_and_Breakfast()

















