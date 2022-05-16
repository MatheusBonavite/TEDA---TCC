import matplotlib.pyplot as plt
fig, ax = plt.subplots()
ax.set_xlim((0, 4.5))
ax.set_ylim((0, 4))

#isolated point
isolated_point = [0.25, 0.25]

#center
center = [3.0, 2.0]

#points generated with gaussian random
points = [[2.832695188718597, 2.2822119035908854],
 [3.2344369547241314, 1.7085186356112405],
 [2.787910244322204, 1.8694800695192089],
 [2.880693610969332, 1.7015829986631164],
 [3.207289384162727, 1.540252813369687],
 [2.5741599229171443, 1.6991434551020204],
 [3.230019575002791, 2.5283433248784792],
 isolated_point]

val = 0
for point in points:
    if(point[0] == isolated_point[0] and point[1] == isolated_point[1]):
        ax.scatter(point[0], point[1] , color='r', s=(250./fig.dpi)**2)
    else:
        ax.scatter(point[0], point[1], color='b', s=(200./fig.dpi)**2)
    if(val + 1 != 5):
        plt.text(point[0] + 0.05,point[1] + 0.05,f"{val + 1}")
    else:
        plt.text(point[0] - 0.1,point[1] - 0.2,f"{val + 1}")
    val = val + 1
ax.scatter(center[0], center[1], color='k', marker='x')
fig.savefig('plot.png', dpi=1200)