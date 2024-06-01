# import library

import math

# enter values

f = int(input('enter frequency: '))
h_b = int(input('enter base station antenna height: '))
h_m = float(input('mobile device antenna height: '))
d = float(input('enter base station and mobile device distance: '))
C = int(input('constant factor: '))

# find the correnction factor a_h_m

a_h_m = (1.11*math.log10(f) - 0.7)*h_m - (1.56*math.log10(f) - 0.8)
print(a_h_m)

# find pathloss

path_loss = 46.3 + (33.9*math.log10(f)) - (13.82*math.log10(h_b)) - a_h_m + ((44.9 - 6.55*math.log10(h_b))*(math.log10(d))) + C
print(path_loss)