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

def waitjob (limit=200) :
    while True :
        if njob() <= limit :
            break
        time.sleep(5)
    return

def submit_job (orgfile, run, start, end):

    with open(orgfile, 'r') as f:
        data = f.read()
        
    data = data.replace('$argv[1]','{}'.format(run))
    data = data.replace('$argv[2]','{}'.format(start))
    data = data.replace('$argv[3]','{}'.format(end))

    filename = './run/job_run{}_{}_{}.sh'.format(run,start,end) 
    with open(filename,mode='w') as f:
        f.write(data)

    ret = subprocess.call('pjsub {} '.format(filename), shell=True)
    logger.info('submit {} ({})'.format(filename, orgfile));
    return 

def loop_one_run (orgfile, run) :
    step = 50000
    for i in range(0,40):
        waitjob()
        submit_job(orgfile, run, i*step, (i+1)*step-1)

def do_data_MIDDLE ():
    runs = [];
    return      
   
#### main
if __name__ == '__main__' :
    
    setup_logger(logfile="./submitlog/log.txt")

    loop_one_run('rec_data_MIDDLE.sh',2798)
