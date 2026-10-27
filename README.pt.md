🇵🇹 Português | [🇬🇧 English](README.md)

# Gestão de Parque de Estacionamento

Programa em C desenvolvido para a unidade curricular de Programação de Computadores da Licenciatura em Engenharia Eletrotécnica e de Computadores do ISEC. Gere um parque de estacionamento com três tipos de lugares: registo de entradas e saídas pela matrícula, cálculo do valor a pagar por tempo de permanência, gestão de clientes fidelizados com desconto e consulta dos lugares disponíveis.

## Funcionalidades

- **Entrada de veículos**: introdução da matrícula, validação do formato e escolha da classe do veículo. Impede a entrada de matrículas já registadas e de veículos quando não há lugares da classe escolhida.
- **Saída de veículos**: pesquisa pela matrícula, cálculo do tempo de permanência e do valor a pagar. Remove o registo do parque.
- **Pesquisa de veículo**: mostra classe e hora de entrada de um veículo estacionado.
- **Clientes fidelizados**: registo de clientes (nome, telefone, matrícula, classe e duração em meses), consulta, remoção e desconto de 20% na saída.
- **Lugares disponíveis**: apresentados no ecrã em todos os menus.
- **Limpeza de base de dados**: apaga os veículos estacionados ou os clientes fidelizados.
- **Persistência**: os dados são guardados em ficheiros binários, pelo que se mantêm entre execuções.

## Classes de veículos

| Classe | Tipo | Lugares |
|--------|------|---------|
| 1 | Mota | 50 |
| 2 | Ligeiro de passageiros | 100 |
| 3 | Ligeiro de mercadorias | 20 |

Se a matrícula já for de um cliente fidelizado, a classe é atribuída automaticamente a partir do registo de fidelização.

## Formato das matrículas

São aceites os seguintes formatos, com ou sem hífen:

- `AA-00-00`
- `00-00-AA`
- `00-AA-00`
- `AA-00-AA`
- Outras combinações alfanuméricas até 9 caracteres, sem hífen

As letras são convertidas para maiúsculas automaticamente.

## Cálculo do preço

O tempo é contado em horas. Qualquer fração de hora conta como hora completa, e o mínimo cobrado é 1 hora. Os valores por hora são:

| Tempo de permanência | Mota | Ligeiro passageiros | Ligeiro mercadorias |
|----------------------|------|---------------------|---------------------|
| 1.ª hora | 0,20 € | 0,50 € | 2,00 € |
| 2.ª a 4.ª hora (por hora) | 0,50 € | 1,00 € | 4,00 € |
| 5.ª a 8.ª hora (por hora) | 1,00 € | 1,50 € | 8,00 € |
| A partir da 9.ª hora (por hora) | 4,00 € | 10,00 € | 20,00 € |

Exemplo: um ligeiro de passageiros que permanece 6 horas paga 0,50 + 3 × 1,00 + 2 × 1,50 = 6,50 €.

### Desconto de fidelização

Se a matrícula estiver fidelizada no momento da saída, o valor é reduzido em 20%.

## Clientes fidelizados

- A duração da fidelização é indicada em meses, considerando meses de 30 dias.
- Quando a fidelização expira, o registo é removido automaticamente ao iniciar o programa.
- Não é possível fidelizar a mesma matrícula duas vezes.

## Requisitos

- Compilador C (GCC com MinGW, ou Visual Studio)
- Sistema operativo **Windows**. O programa usa `conio.h`, `getch()` e `system("cls")`, que não existem em Linux nem em macOS.

## Compilação

Com GCC (MinGW):

```bash
gcc main.c -o parque.exe
```

Para ver avisos do compilador:

```bash
gcc -Wall -Wextra main.c -o parque.exe
```

## Execução

```bash
parque.exe
```

## Utilização

O menu principal tem as seguintes opções:

| Tecla | Opção |
|-------|-------|
| A | Entrada de veículo |
| B | Saída de veículo |
| C | Pesquisa de veículo |
| D | Clientes fidelizados (F: fidelizar, R: remover, C: consultar, S: voltar) |
| E | Limpar base de dados (V: veículos estacionados, F: fidelizados, S: voltar) |
| S | Sair |

As opções são selecionadas com uma única tecla, sem necessidade de Enter.

## Ficheiros gerados

| Ficheiro | Conteúdo |
|----------|----------|
| `veiculos.dat` | Veículos estacionados |
| `fidelizados.dat` | Clientes fidelizados |
| `temp.dat`, `tempf.dat` | Ficheiros temporários usados durante a saída e a remoção (apagados automaticamente) |

Os ficheiros são criados na pasta a partir da qual o programa é executado.

## Estrutura do código

O ficheiro `main.c` contém:

- Estruturas `VEICULO`, `FIDELIZADO` e `LUGARES`
- Menus (`menuP`, `menuB`, `menuD`)
- Entrada e saída (`entradaVeiculo`, `saidaVeiculo`)
- Fidelização (`guardaFidelizado`, `apagaFidelizacao`, `pesquisaFidelizacao`, `verificaFidelizacao`)
- Validação (`validarMatricula`, `validaRegisto`)
- Cálculo do valor (`calcularValor`)
- Contagem de lugares (`contaVeiculos`, `lugaresDisponiveis`)

## Problemas conhecidos

- Na função `contaVeiculos`, os veículos de mercadorias descontam ao contador de passageiros em vez do de mercadorias. O contador de lugares só fica correto até ao primeiro arranque com veículos dessa classe.
- A capacidade de cada classe está fixa no código (constantes `MOTA`, `PASSAGEIROS` e `MERCADORIAS`).

## Autor

Tiago Gaspar, Engenharia Eletrotécnica e de Computadores, ISEC.
