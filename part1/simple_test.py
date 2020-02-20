from docker_runner import get_docker_results
from pprint import pprint as pr

command = 'make build'
pr(get_docker_results(command))

print("MAP TIMES Complicated")
command = './main m c'
pr(get_docker_results(command))

print("PMAP TIMES Complicated")
command = './main p c'
pr(get_docker_results(command))

print("MAP TIMES Simple")
command = './main m s'
pr(get_docker_results(command))

print("PMAP TIMES Simple")
command = './main p s'
pr(get_docker_results(command))


