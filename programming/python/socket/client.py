import socket
import pickle
from method import *


def main():
    host = '127.0.0.1'
    port = 65432
    inputSize, inputNumbersList = createRandomInstance()
    solutionMethod = getSolutionMethodFromUser(inputSize)

    request = {
        'inputSize': inputSize,
        'inputNumbersList': inputNumbersList,
        'solutionMethod': solutionMethod
    }
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client_socket.connect((host, port))

    try:
        client_socket.send(pickle.dumps(request))
        result = client_socket.recv(4096)
        print("Result from server:", pickle.loads(result))
    except Exception as e:
        print(f"Error: {e}")
    finally:
        client_socket.close()


if __name__ == "__main__":
    main()
