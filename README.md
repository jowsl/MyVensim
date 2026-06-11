Markdown
# MyVensim - Simulador de Dinâmica de Sistemas

MyVensim é uma API genérica em C++ projetada para simular modelos de Dinâmica de Sistemas, espelhando comportamentos encontrados em ferramentas profissionais como Vensim. Permite que os usuários modelam estruturas dinâmicas complexas e executem integração numérica contínua.

## Arquitetura Central

O framework é construído sobre três blocos estruturais fundamentais:
* **System:** Representa estoques (como material, população ou energia) que armazenam valores ao longo do tempo.
* **Flow:** Representa os caminhos de transferência e equações diferenciais algébricas conectando os sistemas.
* **Model:** O mecanismo de orquestração responsável por executar a linha do tempo da simulação e garantir atualizações sincronizadas.

---

## Como Compilar e Executar

### Compilar o projeto
Para gerar o binário dos testes funcionais, execute o comando `make` na raiz do projeto:
```bash
make
```
Executar os testes
Para rodar a suíte de testes funcionais e verificar a precisão do simulador:

```bash
make run-func
```
Para rodar os testes unitários, garantindo a integridade dos componentes individuais:
```bash
make run-unit
```

Project Developers
Jouberth Matheus Simão Pereira
Enzo Bigodeiro Bernardes

Note: Developed as an academic assignment for the BCC322 (Software Engineering).