# WiFi Simulator Project

## Overview

The **WiFi Simulator** is a project that simulates the communication behavior of WiFi networks using three different WiFi standards: **WiFi 4 (802.11n)**, **WiFi 5 (802.11ac)**, and **WiFi 6 (802.11ax)**. This simulation evaluates key performance metrics such as throughput, average latency, and maximum latency under different network conditions, including varying numbers of users.

## Problem Statement

The project simulates the behavior of WiFi networks based on three different standards:

1. **WiFi 4 (802.11n)**: Simulates communication with a single access point (AP) and multiple users. It models channel sniffing and packet transmission with backoff times when the channel is busy.
2. **WiFi 5 (802.11ac)**: Introduces multi-user MIMO and parallel communication, where users exchange Channel State Information (CSI) packets before communicating in parallel.
3. **WiFi 6 (802.11ax)**: Implements OFDMA, allowing sub-channel allocation for multiple users to communicate in parallel over smaller frequency blocks.

The goal is to calculate throughput, average latency, and maximum latency for different numbers of users (1, 10, 100) in each WiFi standard scenario.

## Features

- **WiFi 4**: Simulates basic transmission with backoff when the channel is busy.
- **WiFi 5**: Simulates multi-user MIMO with a CSI exchange, followed by parallel communication.
- **WiFi 6**: Implements OFDMA to allow users to communicate over subdivided sub-channels in parallel.



## Prerequisites

Make sure you have the following installed:

- A C++ compiler that supports C++11 or higher (e.g., GCC).
- `make` or any other build tool for compiling the code.


## Usage

You can run the simulation for different WiFi standards with the following parameters:

### Parameters

- `numUsers`: Number of users (e.g., 1, 10, 100).
- `simulationTime`: The total simulation time in milliseconds.
- `subChannelSize` (for WiFi 6): The size of sub-channels in MHz (options: 2, 4, 10 MHz).
- `multiSubChannelAllocation` (for WiFi 6): A boolean flag indicating whether multi-sub-channel allocation is enabled (true/false).


## File Structure

The project contains the following files:

- **main.cpp**: The main driver for the simulation, where user input is handled, and simulations are executed.
- **WiFi4Simulator.cpp**: Contains the logic for simulating WiFi 4 (802.11n) communication.
- **WiFi5Simulator.cpp**: Contains the logic for simulating WiFi 5 (802.11ac) communication with multi-user MIMO.
- **WiFi6Simulator.cpp**: Contains the logic for simulating WiFi 6 (802.11ax) communication using OFDMA.
- **WiFi4Simulator.h**, **WiFi5Simulator.h**, **WiFi6Simulator.h**: Header files defining the classes for WiFi 4, WiFi 5, and WiFi 6 simulators.

## Key Components

### WiFi 4 (802.11n) Simulation:
- **Transmission Mechanism**: Single user transmission with random backoff when the channel is busy.
- **Throughput Calculation**: Based on the symbol rate, modulation, coding rate, and bandwidth.
- **Latency Calculation**: Measures the average and maximum latency for successful transmissions.

### WiFi 5 (802.11ac) Simulation:
- **Multi-user MIMO**: Allows multiple users to communicate in parallel after exchanging CSI packets.
- **Parallel Communication**: Users can transmit in parallel for 15 ms after a broadcast packet.
- **Throughput Calculation**: Adjusts throughput based on the number of users.
- **Latency Calculation**: Includes broadcast latency, CSI exchange latency, and parallel communication latency.

### WiFi 6 (802.11ax) Simulation:
- **OFDMA**: The 20 MHz channel is subdivided into smaller sub-channels (2 MHz, 4 MHz, or 10 MHz).
- **Round-robin Scheduling**: Users are assigned to sub-channels in a round-robin manner.
- **Parallel Transmission**: Users transmit data in parallel for 5 ms per sub-channel.
- **Throughput Calculation**: Scales with the number of users and sub-channels.
- **Latency Calculation**: Includes backoff retries and maximum/average latency.

## Results

The simulation outputs the following metrics for each scenario:

- **Theoretical Max Throughput**: Theoretical maximum throughput based on the given channel parameters.
- **Actual Throughput**: Actual throughput achieved during the simulation.
- **Average Latency**: The average latency of successful transmissions.
- **Maximum Latency**: The maximum latency experienced.
- **Total Data Transmitted**: The total amount of data transmitted during the simulation.
- **Total Successful Transmissions**: The total number of successful transmissions.


