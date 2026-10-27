[🇵🇹 Português](README.pt.md) | 🇬🇧 English

# Car Park Management System

A C program developed for the Computer Programming course (ISEC). It manages a car park with three vehicle classes: entry and exit registration by licence plate, parking fee calculation based on time spent, loyalty customer management with discounts, and a check of available spaces.

## Features

- **Vehicle entry**: enter the licence plate, validate its format and choose the vehicle class. Duplicate plates and entries for a class with no free spaces are refused.
- **Vehicle exit**: look up the plate, calculate the time spent and the amount to pay. The record is then removed from the car park.
- **Vehicle search**: shows the class and entry time of a parked vehicle.
- **Loyalty customers**: register customers (name, phone number, plate, class and duration in months), query them, remove them, and apply a 20% discount at exit.
- **Available spaces**: shown on screen in every menu.
- **Database clearing**: deletes the parked vehicles or the loyalty customers.
- **Persistence**: data is stored in binary files, so it is kept between runs.

## Vehicle classes

| Class | Type | Spaces |
|-------|------|--------|
| 1 | Motorcycle | 50 |
| 2 | Passenger car | 100 |
| 3 | Goods vehicle | 20 |

If the plate belongs to a loyalty customer, the class is assigned automatically from the loyalty record.

## Licence plate format

The following formats are accepted, with or without hyphens:

- `AA-00-00`
- `00-00-AA`
- `00-AA-00`
- `AA-00-AA`
- Other alphanumeric combinations up to 9 characters, without hyphens

Letters are converted to uppercase automatically.

## Fee calculation

Time is counted in hours. Any fraction of an hour counts as a full hour, and the minimum charge is 1 hour. Hourly rates:

| Time spent | Motorcycle | Passenger car | Goods vehicle |
|------------|------------|---------------|---------------|
| 1st hour | €0.20 | €0.50 | €2.00 |
| 2nd to 4th hour (per hour) | €0.50 | €1.00 | €4.00 |
| 5th to 8th hour (per hour) | €1.00 | €1.50 | €8.00 |
| From the 9th hour (per hour) | €4.00 | €10.00 | €20.00 |

Example: a passenger car parked for 6 hours pays 0.50 + 3 × 1.00 + 2 × 1.50 = €6.50.

### Loyalty discount

If the plate is a loyalty customer at the time of exit, the amount is reduced by 20%.

## Loyalty customers

- The loyalty duration is entered in months, with months counted as 30 days.
- When a loyalty period expires, the record is removed automatically when the program starts.
- The same plate cannot be registered as a loyalty customer twice.

## Requirements

- A C compiler (GCC with MinGW, or Visual Studio)
- **Windows**. The program uses `conio.h`, `getch()` and `system("cls")`, which are not available on Linux or macOS.

## Compiling

With GCC (MinGW):

```bash
gcc main.c -o parque.exe
```

To show compiler warnings:

```bash
gcc -Wall -Wextra main.c -o parque.exe
```

## Running

```bash
parque.exe
```

## Usage

The main menu has the following options:

| Key | Option |
|-----|--------|
| A | Vehicle entry |
| B | Vehicle exit |
| C | Vehicle search |
| D | Loyalty customers (F: register, R: remove, C: query, S: back) |
| E | Clear database (V: parked vehicles, F: loyalty customers, S: back) |
| S | Exit |

Options are selected with a single key press, without pressing Enter.

## Generated files

| File | Content |
|------|---------|
| `veiculos.dat` | Parked vehicles |
| `fidelizados.dat` | Loyalty customers |
| `temp.dat`, `tempf.dat` | Temporary files used during exit and removal (deleted automatically) |

The files are created in the folder the program is run from.

## Code structure

`main.c` contains:

- Structures `VEICULO`, `FIDELIZADO` and `LUGARES`
- Menus (`menuP`, `menuB`, `menuD`)
- Entry and exit (`entradaVeiculo`, `saidaVeiculo`)
- Loyalty (`guardaFidelizado`, `apagaFidelizacao`, `pesquisaFidelizacao`, `verificaFidelizacao`)
- Validation (`validarMatricula`, `validaRegisto`)
- Fee calculation (`calcularValor`)
- Space counting (`contaVeiculos`, `lugaresDisponiveis`)

## Known issues

- In `contaVeiculos`, goods vehicles decrement the passenger counter instead of the goods counter. The space counts are only correct from the first start-up with goods vehicles in the file.
- The capacity of each class is fixed in the code (constants `MOTA`, `PASSAGEIROS` and `MERCADORIAS`).

## Author

Tiago Gaspar, Electrical and Computer Engineering, ISEC.
