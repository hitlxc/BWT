#!/usr/bin/python
# -*- coding: utf-8 -*-

from random import random

sequence_file   = 'Sequence.txt'
query_file      = 'Query#9.txt'
NOISE_PERCENT   = 0.4
NOISE_CHARS     = ['x', 'y', 'z', ' ']
QUERY_LENGTH    = [10, 25, 50, 75, 100, 150, 200, 250, 500, 1000]

sequence        = ''
queries         = []

with open(sequence_file, 'r') as sf:
    sequence = sf.read().replace('\n', '')

sequence_length = len(sequence)
for length in QUERY_LENGTH:
    start_index = int(random() * sequence_length)
    end_index   = start_index + length

    if end_index > sequence_length:
        end_index = sequence_length

    query       = sequence[start_index:end_index]
    noise_times = int(length * NOISE_PERCENT)

    for i in range(noise_times):
        operation       = int(random() * 100) % 3
        random_index    = int(random() * length)
        random_char     = NOISE_CHARS[int(len(NOISE_CHARS) * random())]

        if operation == 0:
            # Add a new char
            query = query[:random_index] + random_char + query[random_index:]
        elif operation == 1:
            # Delete a char
            query = query[:random_index] + query[random_index + 1:]
        elif operation == 2:
            # Replace a char
            query = query[:random_index] + random_char + query[random_index + 1:]

    queries.append(query)

with open(query_file, 'w') as qf:
    for q in queries:
        qf.write(q + '\n')
