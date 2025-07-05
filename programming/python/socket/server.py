import socket
import pickle
from method import *


def handle_client(connection, address):
    print(f"Connected to {address}")
    try:
        data = connection.recv(4096)
        if not data:
            return
        request = pickle.loads(data)
        inputSize = request['inputSize']
        inputNumbersList = request['inputNumbersList']
        solutionMethod = request['solutionMethod']
        if solutionMethod[0] == 1:
            result = makeComputationsWithOneProcess(inputSize, inputNumbersList)
        elif solutionMethod[0] == 2:
            result = makeComputationsWithConcurrentProcesses(inputSize, inputNumbersList)
        elif solutionMethod[0] == 3:
            result = makeComputationsWithPoolOfProcesses(inputSize, inputNumbersList,
                                                         numberOfProcesses=solutionMethod[1])
        elif solutionMethod[0] == 4:
            result = makeComputationsWithOneMultithreadedProcess(inputSize, inputNumbersList,
                                                                 numberOfThreadsPerProcess=solutionMethod[1])
        else:
            result = "Program termination requested by user. Exiting..."
        connection.send(pickle.dumps(result))
    except Exception as e:
        print(f"Error: {e}")
    finally:
        connection.close()


def main():
    host = '127.0.0.1'
    port = 65432
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind((host, port))
    server_socket.listen(5)
    print("Server is listening...")

    while True:
        conn, addr = server_socket.accept()
        handle_client(conn, addr)


if __name__ == "__main__":
    main()
