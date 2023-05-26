## ProjetoEDA
# Objetivo
Este projeto é sobre os meios de mobilidade urbana em contexto de uma smart-city. Foi-nos pedido, para realizar a gestão de registos de meios, utilização, etc. O solução desenvolvida, deve ser sobre estruturas de dados dinâmicas, armazenar os dados em ficheiro, apresentação de estrutura e documentação adequadas.
# Primeira Fase
Na primeira fase, tivemos como objetivos os seguintes:
1. Definição de uma estrutura de dados dinâmica (a validar previamente com o docente), para a representação dos meios de mobilidade elétrica, clientes e gestores;
2. Armazenamento/leitura dos dados em ficheiro de texto (valores de simulação) e binários (preservar dados);
3. Inserção de novos dados (cliente/gestor/meio de mobilidade elétrica);
4. Remoção de determinados dados (cliente/gestor/meio de mobilidade elétrica);
5. Alteração de determinados dados (cliente/gestor/meio de mobilidade elétrica);
6. Registo do aluguer de um determinado meio de mobilidade elétrica;
7. Listagem dos meios de mobilidade elétrica por ordem decrescente de autonomia;
8. Listagem dos meios de mobilidade elétrica existentes numa localização com determinado geocódigo;

# Dados para utilizar o menu gestores/clientes

Para conseguir realizar operações com clientes, pode usar o cliente com codigo 1, NIF 192424100.
Para conseguir realizar operações com gestores, pode usar os seguintes:
Codigo 1, senha 1324ESI2023.
Codigo 2, senha Admin1324.
Codigo 3, senha Default1881.

Ambas as senhas do gestor 2 e 3, estão "encriptadas" no ficheiro gestores.

# Segunda Fase
Na segunda fase, tivemos como objetivos os seguintes:
1. Definição de uma estrutura de dados dinâmica para representação da localização de um conjunto de clientes e meios de mobilidade elétrica, recorrendo a um grafo;
2. Armazenamento/leitura dos dados em ficheiro de texto (valores de simulação) e binários (preservar dados). 
3. Dado a localização de um cliente, listar os meios de mobilidade elétrica de um determinado tipo existentes
num determinado raio;
4. Calcular uma solução (adaptação do problema do caixeiro viajante) do trajeto com a menor distância a percorrer, com recurso a um camião, para recolha de todos os meios de mobilidade elétrica com carga da bateria abaixo de 50%. O ponto de partida e chegada é o mesmo. A capacidade de transporte do camião é limitada e dependente dos tipos de meios de mobilidade transportados, pelo que poderá ser necessário efetuar vários circuitos de modo a completar a recolha dos referidos meios de mobilidade elétrica.
