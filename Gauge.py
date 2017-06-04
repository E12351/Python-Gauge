import os, sys
import matplotlib
import numpy as np
from matplotlib import cm
from matplotlib import pyplot as plt
from matplotlib.patches import Circle, Wedge, Rectangle

########################################################################################################################
def degree_range(n): 
    start = np.linspace(0,180,n+1, endpoint=True)[0:-1]
    end = np.linspace(0,180,n+1, endpoint=True)[1::]
    mid_points = start + ((end-start)/2.)
    return np.c_[start, end], mid_points

def rot_text(ang): 
    rotation = np.degrees(np.radians(ang) * np.pi / np.pi - np.radians(90))
    return rotation

########################################################################################################################
def Init_Gauge(fig,ax,ID='Battery ID'):
    labels=['1','2','3','4','5','6','7','8','9','10','11','12','13','14','15','16','17','18','19','20','21','22','23','24']
    colors='jet_r'
    cat=6
    title=''
    fname='./meter.png' 

    N = len(labels)
    if isinstance(colors, str):
        cmap = cm.get_cmap(colors, N)
        cmap = cmap(np.arange(N))
        colors = cmap[::-1,:].tolist()
    if isinstance(colors, list): 
        if len(colors) == N:
            colors = colors[::-1]
        else: 
            raise Exception("\n\nnumber of colors {} not equal to number of categories{}\n".format(len(colors), N))

    # begins the plotting
    ang_range, mid_points = degree_range(N)
    labels = labels[::-1]

    # plots the sectors and the arcs
    patches = []
    for ang, c in zip(ang_range, colors): 
        # sectors
        patches.append(Wedge((0.,0.), .02, *ang, facecolor='w', lw=2))
        # arcs
        patches.append(Wedge((0.,0.), .02, *ang, width=0.005, facecolor=c, lw=0.6, alpha=0.5))

    [ax.add_patch(p) for p in patches]

    # set the labels (e.g. 'LOW','MEDIUM',...)
    # 0.15 represent the r of the circule.
    for mid, lab in zip(mid_points, labels): 
        ax.text(0.018 * np.cos(np.radians(mid)), 0.018 * np.sin(np.radians(mid)), lab,horizontalalignment='center', verticalalignment='center', fontsize=6,fontweight='bold', rotation = rot_text(mid))

    # set the bottom banner and the title
    # r = Rectangle((-0.007,-0.001),0.014,0.002, facecolor='w', lw=2,label='Label')
    # ax.add_patch(r)

    ax.text(0, -0.05, title, horizontalalignment='center',verticalalignment='center', fontsize=22, fontweight='bold')

    # plots the arrow now
    ax.add_patch(Circle((0, 0), radius=0.002, facecolor='k'))
    ax.add_patch(Circle((0, 0), radius=0.001, facecolor='w', zorder=11))  # circle in the arrow.

    #removes frame and ticks, and makes axis equal and tight
    ax.set_frame_on(False)
    ax.axes.set_xticks([])
    ax.axes.set_yticks([])
    ax.axis('equal')
    ax.margins(tight=True)


    ang_range, mid_points = degree_range(N*10)
    # Arrow of the first gauge

    ax.text(-0.004,-0.01 ,ID)   #battery ID
    TX = ax.text(-0.004,-0.006 ,'Value : '+ str(0))
    AR = ax.arrow(0, 0, 0.007 * np.cos(np.radians(0)), 0.007 * np.sin(np.radians(0)),width=0.002, head_width=0.002, head_length=0.01, fc='k', ec='k')
    
    return TX,AR,mid_points
########################################################################################################################
def Update(ax,cat,AR,TX,mid_points):
    AR.remove()
    TX.remove()
    # TX = ax.text(-0.003,-0.004 , "")
    TX = ax.text(-0.003,-0.006 ,'Value : '+ str(cat))
    pos = mid_points[abs(cat - 240)]
    AR = ax.arrow(0, 0, 0.007 * np.cos(np.radians(pos)), 0.007 * np.sin(np.radians(pos)),width=0.002, head_width=0.002, head_length=0.01, fc='k', ec='k')
    plt.ion() 
    plt.pause(0.0001)
    return AR,TX
########################################################################################################################
fig, ((ax, ax2,ax3,ax4,ax5),(ax6,ax7,ax8,ax9,ax10)) = plt.subplots(2, 5, sharex=True,sharey=True)
fig.set_size_inches(13.0, 5.0)

TX1 ,AR1 , mid_points1 = Init_Gauge(fig,ax,"Battery 1")
TX2 ,AR2 , mid_points2 = Init_Gauge(fig,ax2)
TX3 ,AR3 , mid_points3 = Init_Gauge(fig,ax3)
TX4 ,AR4 , mid_points4 = Init_Gauge(fig,ax4)
TX5 ,AR5 , mid_points5 = Init_Gauge(fig,ax5)
TX6 ,AR6 , mid_points6 = Init_Gauge(fig,ax6)
TX7 ,AR7 , mid_points7 = Init_Gauge(fig,ax7)
TX8 ,AR8 , mid_points8 = Init_Gauge(fig,ax8)
TX9 ,AR9 , mid_points9 = Init_Gauge(fig,ax9)
TX10 ,AR10 , mid_points10 = Init_Gauge(fig,ax10)

plt.subplots_adjust(left=0, bottom=0, right=1, top=1, wspace=0, hspace=0)
plt.setp(ax,adjustable='box-forced')
########################################################################################################################
for x in xrange(1,10):
    # print x
    AR1,TX1 = Update(ax,x,AR1,TX1,mid_points1)
    # AR2 = Update(ax2,x,AR2,mid_points2)
    pass
########################################################################################################################
print "Finished."
raw_input()
