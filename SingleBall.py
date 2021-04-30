import math
num = input("How many balls are there? ")
num = int(num)
balls = []
distarry = []

for x in range(0,num):
    ballpos = input("Enter the X,Y coords of ball number " +str(x+1) + ": ")
    balls.append(ballpos)

hippopos = input("Enter the X,Y coords of the hippo: ")

hippox,hippoy = hippopos.split(',')

minball = balls[0]
mindist = 9999

for x in range(0,num):
    currball = balls[x]
    ballx,bally = currball.split(',')
    
    xchange = float(ballx) - float(hippox)
    ychange = float(bally) - float(hippoy)

    dist = math.sqrt(pow(xchange,2) + pow(ychange,2))
    if(dist < mindist):
        mindist = dist
        minball = balls[x]
        minposarry = x
    
ballx,bally = balls[minposarry].split(',')
xchange = float(ballx) - float(hippox)
ychange = float(bally) - float(hippoy)

angle = math.atan2(ychange,xchange)
angle = math.degrees(angle)
print("Ball number " + str(minposarry+1) + " is the closest")
print(mindist)
print(angle)