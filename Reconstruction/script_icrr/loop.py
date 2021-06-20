import subprocess
import time
from logging import getLogger, StreamHandler, Formatter, FileHandler, DEBUG


logger = getLogger(__name__)

def setup_logger (logfile='submitlog.txt'):
    logger = getLogger(__name__)
    logger.setLevel(DEBUG)

    sh = StreamHandler()
    sh.setLevel(DEBUG)
    formatter = Formatter('%(asctime)s: %(message)s')
    sh.setFormatter(formatter)
    logger.addHandler(sh)

    fh = FileHandler(logfile) #fh = file handler
    fh.setLevel(DEBUG)
    fh_formatter = Formatter('%(asctime)s : %(message)s')
    fh.setFormatter(fh_formatter)
    logger.addHandler(fh)
    return logger
    

def njob () :
    ret = subprocess.check_output('pjstat | grep menjo | wc', shell=True)
    vals = ret.split()
    n = int(vals[0])
    return n

def waitjob (limit=300) :
    while True :
        if njob() <= limit :
            break
        time.sleep(10)
    return

def submit_job (orgfile, run, start=0, end=1000000, tag='job'):

    with open(orgfile, 'r') as f:
        data = f.read()
        
    data = data.replace('$argv[1]','{}'.format(run))
    data = data.replace('$argv[2]','{}'.format(start))
    data = data.replace('$argv[3]','{}'.format(end))

    filename = './run/{}_run{}_{}_{}.sh'.format(tag,run,start,end) 
    with open(filename,mode='w') as f:
        f.write(data)

    ret = subprocess.call('pjsub {} '.format(filename), shell=True)
    logger.info('submit {} ({})'.format(filename, orgfile));
    return 

def submit_job_pede (orgfile, run, dirtag, tag='job'):

    with open(orgfile, 'r') as f:
        data = f.read()
        
    data = data.replace('$argv[1]','{}'.format(run))
    data = data.replace('$argv[2]','{}'.format(dirtag))

    filename = './run/{}_pede_run{}_{}_{}.sh'.format(tag,run) 
    with open(filename,mode='w') as f:
        f.write(data)

    #ret = subprocess.call('pjsub {} '.format(filename), shell=True)
    #logger.info('submit {} ({})'.format(filename, orgfile));
    return 
    

def loop_one_run (orgfile, run) :
    step = 50000
    for i in range(0,40):
        waitjob()
        submit_job(orgfile, run, i*step, (i+1)*step-1)
    return 

#### Loop for specific data sets
runs_fill21142 = [2631, 2632, 2633, 2634, 2636, 2637, 2641, 2644]
runs_fill21145 = [2718, 2721, 2726, 2730, 2732, 2734, 2736, 2738, 2740]
runs_fill21148 = [2798, 2801, 2803, 2812, 2818, 2819, 2823, 2824, 2827]
runs_fill21149 = [2845, 2847, 2850, 2852, 2854, 2857, 2864, 2867, 2868, 2878, 2881, 2883, 2887, 2889, 2892, 2896, 2899, 2903, 2905]
runs_fill21150 = [2924, 2932, 2933, 2937, 2939, 2947, 2954, 2956, 2958, 2960, 2964, 2966, 2968, 2970, 2972, 2973, 2979, 2981, 2983]
                        
def do_data_MIDDLE_1 ():
    orgfile = 'rec_data_MIDDLE.sh'
    for run in runs_21148:
        loop_one_run(orgfile, run)
    return

def do_data_MIDDLE_2 ():
    orgfile = 'rec_data_MIDDLE.sh'
    for run in runs_fill21150:
        loop_one_run(orgfile, run)
    return

def do_data_BOTTOM_1 ():
    orgfile = 'rec_data_BOTTOM.sh'
    for run in runs_fill21142:
        loop_one_run(orgfile, run)
    return

def do_data_BOTTOM_2 ():
    orgfile = 'rec_data_BOTTOM.sh'
    for run in runs_fill21145:
        loop_one_run(orgfile, run)
    return

def do_data_TOP ():
    orgfile = 'rec_data_TOP.sh'
    for run in runs_fill21149:
        loop_one_run(orgfile, run)
    return    

def do_EPOSLHC_MIDDLE ():
    orgfile = 'rec_EPOS_MIDDLE.sh'
    for run in range(1,1000):
         submit_job (orgfile, run, tag='eposlhc')
    return 

def do_pede ():
    orgfile = 'pede_data.sh'
    runlist = [runs_fill21142, runs_fill21145, runs_fill21148, runs_fill21149, runs_fill21150]
    dirtags = ['BOTTOM_1', 'BOTTOM_2', 'MIDDLE_1', 'TOP', 'MIDDLE_2']
    for i in range(0,5):
        for run in runlist[i]:
            submit_job_pede (run, dirtags[i])
    return                     
    
   
#### main
if __name__ == '__main__' :
    
    setup_logger(logfile="./submitlog/log.txt")

    # Pedestal
    
    #do_pede();

    # Data 
    #do_data_MIDDLE_1 ()
    #do_data_MIDDLE_2()
    #do_data_BOTTOM_1()
    #do_data_BOTTOM_2()    
    #do_data_TOP()

    # MC
    #do_EPOSLHC_MIDDLE ()
