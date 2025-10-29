# 🎮 Genius Game com Arduino

Um projeto completo do clássico **jogo da memória “Simon”**, desenvolvido em **Arduino**, com **LEDs coloridos, botões interativos, sons** e agora um **display digital TM1637** que exibe mensagens como **“Hi”** e **“Good”** 🎉  

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
  Segure o botão **amarelo** ao iniciar o jogo para desbloquear uma **melodia disco animada** com LEDs piscando no ritmo! 🕺

- 🖥️ **Novo: Display TM1637 integrado**  
  Exibe mensagens dinâmicas:
  - “Hi” → quando o jogador pressiona um botão para começar o jogo.  
  - “Good” → ao acertar uma rodada.  
  - Contagem numérica das rodadas.  
  - Mensagens “bye” e efeitos visuais ao final da partida.

---

## 🧩 Componentes Utilizados

| Componente | Quantidade | Função |
|-------------|-------------|--------|
| Arduino (UNO ou compatível) | 1 | Microcontrolador principal |
| LEDs (Vermelho, Verde, Azul, Amarelo) | 4 | Indicação visual |
| Resistores (220Ω a 330Ω) | 4 | Proteção dos LEDs |
| Botões (push buttons) | 4 | Entrada do jogador |
| Buzzers piezoelétricos | 2 | Emissão de sons |
| **Display TM1637 (4 dígitos)** | 1 | Exibição de mensagens e pontuação |
| Jumpers e Protoboard | - | Conexões elétricas |

---

## ⚙️ Configuração dos Pinos

| Função | Pino | Observação |
|--------|------|-------------|
| LED Vermelho | D10 | Saída |
| LED Verde | D3 | Saída |
| LED Azul | D13 | Saída |
| LED Amarelo | D5 | Saída |
| Botão Vermelho | D9 | Entrada com pull-up |
| Botão Verde | D2 | Entrada com pull-up |
| Botão Azul | D12 | Entrada com pull-up |
| Botão Amarelo | D6 | Entrada com pull-up |
| Buzzer 1 | D4 | Saída de som |
| Buzzer 2 | D7 | Saída de som |
| TM1637 CLK | D8 | Clock do display |
| TM1637 DIO | D11 | Dados do display |

---

## 🕹️ Como Jogar

1. **Ligue o Arduino** — as luzes entram no **modo de espera animado**.  
2. **Pressione qualquer botão** para começar o jogo — o display mostrará **“Hi”**.  
3. Observe a sequência de LEDs e sons.  
4. **Repita exatamente a sequência** pressionando os botões correspondentes.  
5. A cada acerto, o display mostra **“Good”** e a pontuação é atualizada.  
6. Se errar ou demorar mais de **3 segundos**, o jogo termina com a mensagem **“bye”**.  
7. Chegue até **13 rodadas** para vencer! 🏆

---

## 🔧 Modos Especiais

- **Modo Memória (padrão)**: inicia automaticamente.  
- **Modo Batalha**: segure o botão **verde** ao iniciar.  
- **Modo Bee Gees**: segure o botão **amarelo** ao ligar para tocar uma música secreta 🎶  

---

## 🖥️ Exibições do Display TM1637

| Situação | Exibição | Descrição |
|-----------|-----------|------------|
| Início do jogo | **Hi** | Saudação inicial ao pressionar um botão |
| Acerto | **Good** | Mostra a mensagem de acerto |
| Fim do jogo | **bye** | Mostra mensagem de encerramento |
| Rodadas | **Número** | Mostra o total de acertos (1 a 13) |
| Efeitos especiais | Piscar e varredura | Usados em vitórias e animações |

---

## 🏁 Objetivo Educacional

Este projeto é ideal para **iniciantes em eletrônica e programação Arduino**, abordando:  
- Estruturas condicionais (`if`, `switch`)  
- Uso de arrays e funções  
- Temporização com `millis()` e `delay()`  
- Controle de hardware digital (LEDs, botões, buzzers e displays)

---

## 📄 Licença

Este projeto é disponibilizado sob a licença **MIT**.  
Sinta-se livre para **modificar, aprender e compartilhar**! 💡

---

## 🧠 Créditos

Desenvolvido para fins **educacionais** e de **aprendizado em lógica e eletrônica interativa**.  
Inspirado no clássico **“Simon Says”** da década de 1980.

**Full Changelog**:  
https://github.com/guilhermecoding/genius-game-arduino/compare/v1.0.0...v1.0.0
