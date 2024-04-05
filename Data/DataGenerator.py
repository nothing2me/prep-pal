import random
import string

def random_string():
  """
  Returns a random string used for a first or last name
  :return random str of 6 chars
  """

  length = random.randrange(4,8)
  string.ascii_letters = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'
  return ''.join(random.choice(string.ascii_letters) for i in range(length))

def generate_data(num_records):
  """
  :param num_records
  :return data
  """
  data = []
  for _ in range(num_records):
    # Student ID (random number)
    student_id = random.randint(1000000, 9999999)

    # Transfer student flag (0 or 1)
    transfer_status = random.randint(0, 1)

    # Attempted college hours (random number)
    attempted_hours = random.randint(0, 120)

    # Tsi attempts (random numbers between 0 and 3)
    math_tsi_attempts = random.randint(0, 3)
    reading_tsi_attempts = random.randint(0, 3)

    # Course scores (random numbers between 0 and 300)
    math_score = random.randint(0, 300)
    reading_score = random.randint(0, 300)
    writing_score = random.randint(0, 300)

    last_name = random_string()
    first_name = random_string()

    # Generate data record
    data_record = f"A0{student_id:07},email@islander.tamucc.edu,{last_name},{first_name:05},{transfer_status}," \
                  f"{attempted_hours:03},{math_tsi_attempts:02},{reading_tsi_attempts:02},{math_score:03},{reading_score:03},{writing_score:03}"

    data.append(data_record)

  return data


def main():
  """
  Prompt user for how many lines of data to generate
  """
  datafile = open("data.txt", "w")

  num_records = int(input("Enter the number of records to generate: "))

  data = generate_data(num_records)

  for record in data:
    print(record)
    datafile.writelines(f"{record}\n")

  datafile.close()
if __name__ == "__main__":
  main()
