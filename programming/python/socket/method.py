import random
import time
import multiprocessing
from threading import Thread, Lock
from datetime import datetime

def getTimeInMilliseconds():
    return int(time.time() * 1000)

def createRandomInstance():
    try:
        inputSize = int(input("🔢 Πόσους αριθμούς θέλεις να επεξεργαστείς; "))
    except ValueError:
        print("⚠️ Μη έγκυρη είσοδος. Ορίζεται προεπιλεγμένο μέγεθος: 5")
        inputSize = 5


    inputNumbersList = random.sample(range(1, 101), inputSize)
    print(f"📦 Δημιουργήθηκε λίστα: {inputNumbersList}")
    return inputSize, inputNumbersList


def getSolutionMethodFromUser(inputSize):
    print("\n📌 Επιλογές μεθόδου υπολογισμού:")
    print("1. Υπολογισμός με μία διεργασία (single process)")
    print("2. Υπολογισμός με πολλαπλές διεργασίες (concurrent processes)")
    print("3. Υπολογισμός με pool διεργασιών (process pool)")
    print("4. Υπολογισμός με μία πολυνηματική διεργασία (multithreaded process)")
    print("0. Έξοδος")

    while True:
        try:
            choice = int(input("🔢 Δώσε επιλογή (0-4): "))
            if choice == 0:
                return [0]
            elif choice == 1 or choice == 2:
                return [choice]
            elif choice == 3:
                num_processes = int(input(f"⚙️  Πόσες διεργασίες να χρησιμοποιηθούν (1 έως {inputSize}): "))
                return [3, max(1, min(num_processes, inputSize))]
            elif choice == 4:
                num_threads = int(input(f"🧵 Πόσα νήματα να χρησιμοποιηθούν (1 έως {inputSize}): "))
                return [4, max(1, min(num_threads, inputSize))]
            else:
                print("❌ Μη έγκυρη επιλογή. Προσπάθησε ξανά.")
        except ValueError:
            print("⚠️ Παρακαλώ δώσε έναν αριθμό.")

def calculate_square(inputTriple):
    thread_name, number, shared_dict = inputTriple
    result = number ** 2
    time.sleep(1)
    shared_dict[number] = result
    print(f"{thread_name}: {number}^2 = {result}")





def makeComputationsWithOneProcess(inputSize, inputNumbersList):
    start_time = getTimeInMilliseconds()
    result_dict = {}
    for number in inputNumbersList:
        calculate_square(("", number, result_dict))
    end_time = getTimeInMilliseconds()
    print(f"Single process computation completed in {end_time - start_time} ms")
    return result_dict


def makeComputationsWithConcurrentProcesses(inputSize, inputNumbersList):
    start_time = getTimeInMilliseconds()
    manager = multiprocessing.Manager()
    result_dict = manager.dict()
    processes = []

    for number in inputNumbersList:
        process = multiprocessing.Process(target=calculate_square, args=(("", number, result_dict),))
        processes.append(process)
        process.start()

    for process in processes:
        process.join()

    end_time = getTimeInMilliseconds()
    print(f"Concurrent processes completed in {end_time - start_time} ms")
    return dict(result_dict)


def makeComputationsWithPoolOfProcesses(inputSize, inputNumbersList, numberOfProcesses):
    manager = multiprocessing.Manager()
    shared_dict = manager.dict()
    pool = multiprocessing.Pool(processes=numberOfProcesses)
    tasks = [("Process-" + str(i + 1), number, shared_dict) for i, number in enumerate(inputNumbersList[:inputSize])]
    start_time =getTimeInMilliseconds()
    pool.map(calculate_square, tasks)
    pool.close()
    pool.join()
    end_time = getTimeInMilliseconds()
    total_time = end_time - start_time
    print(f"Total computation time: {total_time:} ms")
    return dict(shared_dict)


def makeComputationsWithOneMultithreadedProcess(inputSize, inputNumbersList, numberOfThreadsPerProcess):
    start_time = getTimeInMilliseconds()
    result_dict = {}
    threads = []
    lock = Lock()

    def thread_safe_calculate(inputTriple):
        thread_name, number = inputTriple
        result = number ** 2
        time.sleep(1)
        with lock:
            result_dict[number] = result
        print(f"{thread_name}: {number}^2 = {result}")
    for idx, number in enumerate(inputNumbersList):
        thread_name = f"Thread-{idx + 1}"
        thread = Thread(target=thread_safe_calculate, args=((thread_name, number),))
        threads.append(thread)
        thread.start()

    for thread in threads:
        thread.join()

    end_time = getTimeInMilliseconds()
    print(f"Multithreaded computation completed in {end_time - start_time} ms")
    return result_dict