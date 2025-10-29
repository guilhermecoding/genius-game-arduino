# 🎮 Simon Game com Arduino

Um projeto completo do clássico **jogo da memória “Simon”**, desenvolvido em **Arduino**, com **LEDs coloridos, botões interativos e sons** emitidos por um buzzer duplo.  
O objetivo é testar a memória e a concentração do jogador, repetindo corretamente as sequências de luzes e sons que o sistema reproduz.

---

## ✨ Funcionalidades Principais

- 🧠 **Modo Memória**  
  O jogo gera uma sequência de cores e sons que o jogador deve repetir corretamente.  
  A cada rodada, a sequência aumenta e o desafio fica mais difícil.

- ⚔️ **Modo Batalha (2 jogadores)**  
  Jogadores se alternam adicionando um novo passo à sequência.  
  Quem errar a ordem ou demorar demais... perde!

- 🎵 **Easter Egg: Modo Bee Gees!**  
  Segure o botão **amarelo** ao iniciar o jogo para desbloquear uma **melodia disco animada** com LEDs piscando no ritmo!

---

## 🧩 Componentes Utilizados

| Componente | Quantidade | Função |
|-------------|-------------|--------|
| Arduino (UNO ou compatível) | 1 | Microcontrolador principal |
| LEDs (Vermelho, Verde, Azul, Amarelo) | 4 | Indicação visual |
| Resistores (220Ω a 330Ω) | 4 | Proteção dos LEDs |
| Botões (push buttons) | 4 | Entrada do jogador |
| Buzzers piezoelétricos | 2 | Emissão de sons |
| Jumpers e Protoboard | - | Conexões elétricas |

---

## ⚙️ Configuração dos Pinos

| Cor / Função | LED | Botão | Frequência (Hz) |
|---------------|------|--------|----------------|
| 🔴 Vermelho | D10 | D9 | 440 |
| 🟢 Verde | D3 | D2 | 880 |
| 🔵 Azul | D13 | D12 | 587 |
| 🟡 Amarelo | D5 | D6 | 784 |
| 🔊 Buzzer 1 | D4 | — | — |
| 🔊 Buzzer 2 | D7 | — | — |

---

## 🕹️ Como Jogar

1. **Ligue o Arduino** — as luzes piscarão em modo “atração”.  
2. **Pressione qualquer botão** para começar o jogo.  
3. Observe a sequência de LEDs e sons.  
4. **Repita exatamente a sequência** pressionando os botões.  
5. A cada acerto, o jogo adiciona um novo passo.  
6. **Errou ou demorou mais de 3 segundos?** Perde o jogo.  
7. Chegue até **13 rodadas** para vencer! 🏆

---

## 🔧 Modos Especiais

- **Modo Memória (padrão)**: inicia automaticamente.  
- **Modo Batalha**: segure o botão **verde** ao iniciar.  
- **Modo Bee Gees**: segure o botão **amarelo** ao ligar para tocar uma música secreta 🎶  

---

## 🏁 Objetivo Educacional

Este projeto é ideal para **iniciantes em eletrônica e programação Arduino**, abordando:  
- Estruturas condicionais (`if`, `switch`)  
- Uso de arrays e funções  
- Temporização com `millis()` e `delay()`  
- Controle de hardware digital (LEDs, botões, buzzers)

---

## 📄 Licença

Este projeto é disponibilizado sob a licença **MIT**.  
Sinta-se livre para **modificar, aprender e compartilhar**! 💡

---

## 🧠 Créditos

Desenvolvido para fins **educacionais** e de **aprendizado em lógica e eletrônica interativa**.  
Inspirado no clássico **“Simon Says”** da década de 1980.