
# Mini CPU; Potencia
> Desafio em sala de aula pelo professor Roni de Infraestrutura de Hardware para construir um simulador da MiniCPU usando C ou Python.
> O grupo deve pré-carregar na memória do simulador tanto as instruções (em formato numérico/hexadecimal) quanto os dados iniciais, e então rodar o ciclo F-D-E até o HALT.
> O foco é demonstrar que o simulador funciona corretamente para o problema dado.
> (Pré-carregar BASE=3 em 0x10 e EXP=4 em 0x11. Calcular BASE^EXP por multiplicações via soma repetida. Resultado em 0x20. Validar com: 81.)
<p align = "center">
<img width="500" height="300" alt="CPU-Creditos:Pixabay" src="https://cdn12.picryl.com/photo/2016/12/31/processor-cpu-board-computer-communication-4b0826-1024.jpg" />
</p>

## 💻 Pesquisa e Planejamento
### BUSCA → DECODIFICAÇÃO → EXECUÇÃO (FETCH → DECODE → EXECUTE);

### Interpretação do desafio; 
Pré-carregar BASE=3 (tem três como base) em 0x10 (hexadecimal para o número 16) para e EXP=4 (expoente quatro) em 0x11 (hexadecimal para o número 17). Calcular
BASE^EXP (3^4) por multiplicações via soma repetida(ou seja, 3+3+3+3+3+3+3+3+3+3+3+3). Resultado em 0x20 (hexadecimal para o número 32). Validar com: 81.

## 🚀 Implementação
Utilizamos o esqueleto em C providenciado pelo professor Roni (creditos: https://github.com/0x03c1/CPU-WARS.git)
## ☕ Teste e Trace

## 🤝 Colaboradores

Agradecemos às seguintes pessoas que contribuíram para este projeto:

<table>
  <tr>
    <td align="center">
      <a href="https://github.com/aceamanda" title="Github Amanda">
        <img src="https://avatars.githubusercontent.com/u/205168124?v=4" width="100px;" alt="Foto de Amanda Bormann"/><br>
        <sub>
          <b>Amanda Bormann</b>
        </sub>
      </a>
    </td>
    <td align="center">
      <a href="https://github.com/Davi-Lucena-Costa" title="Github Davi">
        <img src="https://avatars.githubusercontent.com/u/212424400?v=4" width="100px;" alt="Foto de Davi Lucena"/><br>
        <sub>
          <b>Davi Lucena</b>
        </sub>
      </a>
    </td>
    <td align="center">
      <a href="https://github.com/vitoriaduran" title="Github Vitoria">
        <img src="https://avatars.githubusercontent.com/u/172305757?v=4" width="100px;" alt="Foto de Vitória Gabrielle"/><br>
        <sub>
          <b>Vitória Gabrielle</b>
        </sub>
      </a>
    </td>
  </tr>
</table>
