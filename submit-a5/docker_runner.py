import os
# Format String for the time command
IMAGE = "a5-test"


TIME_FORMAT = """
TIME_FORMAT_STRING_INCOMMING
real_time:%e
user_time:%U
system_time:%S
cpu_percent:%P
avg_stack_size_kbytes:%p
mem_swaped:%W
avg_total_mem_kbytes:%K
max_res_set_size_kbytes:%M
avg_res_set_size_kbytes:%t
major_page_faults:%F
minor_page_faults:%R
voluntary_context_switches:%w
involuntary_context_switches:%c
file_system_input_calls:%I
file_system_input_calls:%O
exit_status:%x
""".replace('\n', "*")


def run_in_docker(cmd: str, cpu=None, mem=None, mem_swap=None) -> ():
    """
    Runs the command string in the docker image that is built in the make file
    """
    cpu = 2 if cpu is None else cpu
    mem = 2048 if mem is None else mem
    mem_swap = mem if mem_swap is None else mem_swap
    command ='docker run -it --cpus={} --memory={}m --memory-swap={}m -v "`pwd`":/dockershare {} bash -c "'.format(cpu, mem, mem_swap, IMAGE) + cmd + '"'
    output = os.popen(command)
    return output.read()

def parse_all_time_results(output: str) -> (str, dict):
    """
    Takes an output of a time command and returns the a dictionary
    of those values 
    returns two things
    1. str: The output of the program
    2. dict: The timing results
    """
    items = output.split('*') 
    call_result = '*'.join(items[:items.index('TIME_FORMAT_STRING_INCOMMING')])
    items = items[items.index('TIME_FORMAT_STRING_INCOMMING') + 1:-1]
    result_map =  {}
    # print(items)
    for [k, v] in [s.split(':') for s in items]:
        v = v.replace('%', '')
        v = v.replace('?', '0')
        result_map[k] = float(v)
    return (call_result, result_map)

def get_docker_results(cmd: str, cpu=None, mem=None, mem_swap=None) -> (str, str, dict):
    """
    This function will run a command (cmd) in docker and return three things
    1. str:  The output of the docker command
    2. str:  Sorer output
    2. dict: The parsed output of all the values as a dictionary
    """
    cmd = ('cd /dockershare && /usr/bin/time -f "{}" {}'.format(TIME_FORMAT, cmd))
    output = run_in_docker(cmd, cpu=cpu, mem=mem, mem_swap=mem_swap)
    (result, time_map) = parse_all_time_results(output)
    return (output, result, time_map)











"""

 ██████╗ ██████╗ ██████╗ ███████╗     ██████╗ ██████╗  █████╗ ██╗   ██╗███████╗██╗   ██╗ █████╗ ██████╗ ██████╗ 
██╔════╝██╔═══██╗██╔══██╗██╔════╝    ██╔════╝ ██╔══██╗██╔══██╗██║   ██║██╔════╝╚██╗ ██╔╝██╔══██╗██╔══██╗██╔══██╗
██║     ██║   ██║██║  ██║█████╗      ██║  ███╗██████╔╝███████║██║   ██║█████╗   ╚████╔╝ ███████║██████╔╝██║  ██║
██║     ██║   ██║██║  ██║██╔══╝      ██║   ██║██╔══██╗██╔══██║╚██╗ ██╔╝██╔══╝    ╚██╔╝  ██╔══██║██╔══██╗██║  ██║
╚██████╗╚██████╔╝██████╔╝███████╗    ╚██████╔╝██║  ██║██║  ██║ ╚████╔╝ ███████╗   ██║   ██║  ██║██║  ██║██████╔╝
 ╚═════╝ ╚═════╝ ╚═════╝ ╚══════╝     ╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═╝  ╚═══╝  ╚══════╝   ╚═╝   ╚═╝  ╚═╝╚═╝  ╚═╝╚═════╝ 
                                                                                                                
"""

def _parse_time_results(output: str) -> dict:
    """
    Depricated in favorof parse all time results
    Takes an output of a time command and returns the a dictionary
    of those values 
    """
    # output.split('\n')[-4:-1] = ['real\t0m0.001s', 'user\t0m0.000s', 'sys\t0m0.000s']
    # [s.split('\t') for s in output.split('\n')[-4:-1]] = [['real', '0m0.119s'], ['user', '0m0.030s'], ['sys', '0m0.020s']]
    result_map = {}
    for [k, v] in [s.split('\t') for s in output.split('\n')[-4:-1]]:
        [minutes, seconds] = v.split('m')
        time = float(minutes) * 60.0 + float(seconds.replace('s', ''))
        result_map[k] = time
    return result_map


# client = docker.from_env()

# container_id = docker.APIClient.create_container(
#     'ubuntu-test', 'ls', volumes=['/out'],
#     host_config=docker.utils.create_host_config(binds=[
#         '/temp:/out',
#     ])
# )


# print(cli.containers())

# client.volumes.create(name='/out', driver='out');
# print(client.containers.run("testing-image", "(cd /out && ./sorer_0 -f \"data.sor\" -from 0 -len 1000 -print_col_type 0)"))
# cwd = str(os.getcwd()).replace(' ', '\ ')

# def run_in_docker(cmd):
#     cmd = '"' + cmd + '"'
#     commands = 'docker run -t -v '.split() 
#     commands.append(cwd + '/out:/out')
#     commands.extend('ubuntu:18.04 bash -c '.split(' '))
#     commands.append(cmd)
#     return commands

# cmd = "time -p > /out/time.txt"


# p = subprocess.Popen(run_in_docker(cmd), stdout=subprocess.PIPE)
# out, err = p.communicate()

# print(' '.join(run_in_docker(cmd)))
# # out = (subprocess.check_output(run_in_docker(cmd), stderr=subprocess.STDOUT))

# # os.wait()
# print(out)

# print(str(run_in_docker("cd out && ls")))
# print(timeit(stmt = run_in_docker("time -p cd / && ls"), setup = "import subprocess", number = 1))
