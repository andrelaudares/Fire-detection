NOME:                  RA:
ANDRÉ LAUDARES         22001646
MATHEUS MARAFOM        22004817
RAUL MIGLIARI          22005575


# Simulação de Sistema de Detecção de Incêndios

Este projeto implementa uma simulação de um sistema de detecção de incêndios em uma floresta, utilizando programação paralela e distribuída com `pthreads` e monitores para comunicação e sincronização entre as threads.

## Descrição

O sistema simula uma floresta dividida em uma grade de células 30x30. Cada célula contém um nó sensor que monitora o estado da sua área. Os nós comunicam entre si quando detectam incêndios, propagando mensagens aos vizinhos. Se um nó estiver localizado na borda da matriz, ele envia a mensagem para uma thread central responsável por registrar e gerenciar os eventos de incêndio e iniciar um combate ao fogo. Além disso, o sistema inclui uma thread separada para gerar incêndios aleatórios.

## Funcionalidades

- **Matriz da Floresta**: Representada como uma matriz 30x30 com células que podem ter diferentes estados:
  - `-`: Área livre.
  - `@`: Célula em chamas (fogo ativo).
  - `/`: Célula queimada.
  - `D`: Célula detectada por um sensor.

- **Nó Sensor**: Cada nó é representado por uma thread independente que se comunica com seus vizinhos usando monitores. As funções de comunicação garantem exclusão mútua e comunicação segura utilizando mutexes e variáveis de condição.

- **Thread Geradora de Incêndios**: Gera incêndios aleatórios em diferentes posições da matriz a cada 3 segundos.

- **Central de Controle**: Coleta mensagens dos nós de borda e age para combater incêndios.

## Requisitos Atendidos

1. **Componente Visual**: A matriz é impressa no terminal, e logs são gerados para registrar os eventos dos nós sensores e ações da central.
2. **Sincronização e Exclusão Mútua**: Implementadas usando mutexes e variáveis de condição.
3. **Thread Geradora de Incêndios**: Implementada para gerar incêndios aleatórios a cada 3 segundos.

## Melhorias Possíveis

- Reduzir a redundância de detecção de incêndios pelos sensores.
- Melhorar a visualização da matriz no terminal.
- Adicionar logs mais detalhados para facilitar o monitoramento.

## Como Executar

1. Compile o projeto usando o comando:
   ```bash
   gcc -o fire_simulation main.c functions.c -lpthread
   ```

2. Execute o programa:
   ```bash
   ./fire_simulation
   ```

## Contribuição

Sinta-se à vontade para contribuir com melhorias ou novas funcionalidades. Faça um fork do repositório, crie uma branch para suas alterações e envie um pull request.

## Licença

Este projeto está licenciado sob a [MIT License](LICENSE).
