# WebLight - controle de dispositivos

#### Professor: Wilian França Costa

#### Autor:
- Pedro Padilha Farroco - 31825672

## Objetivo do Trabalho

Desenvolver uma soluçaão

## Pré-requisitos

**1. Computador:** Embora o dispositivo utilizado seja o NodeMCU, utilizamos a IDE do Arduino para programaá-lo. Ela pode ser encontrada [aqui](https://www.arduino.cc/en/Main/Software)

**2. IDE Arduino**: Na IDE, voceê deve instalar as placas da "famiília" ESP8266. Para isso, copie o link em [esp8266-board-download-link.txt](esp8266-board-download-link.txt) e cole no local especificado na janela de Prefereências. (Ctrl + , ou ⌘ + ,). Depois, em BTools>Board>Board Manager, procure por ESP8266 e instale o pacote de placas.

**3. Pessoais:** Embora não seja necessário para a execução do projeto, é bom ter conhecimentos sobre a linguagem de programação do Arduino para entender o funcionamento dele (e também fazer alterações, caso seja do seu interesse)

## Hardware
###### Utilizaremos um LED e um botão para a demonstração

1. NodeMCU

    ![placa](images/nodemcu.jpg)

2. LED

    ![led](images/led.jpg)

3. Switch

    ![switch](images/switch.jpg)

## Instalação

1. Para clonar o repositório, utilize o comando a seguir:

    ```
    git clone https://github.com/pedropadilha13/WebLight.git
    ```

	Uma outra alternativa é baixar o projeto no formato zip, clicando no botão verde acima.

2. Na raiz do projeto, existe um diretório chamado "PubSubClient". Este diretório contém a biblioteca MQTT que a placa utilizará para conectar-se com o broker MQTT. Ele deve ser movido para o diretório ```Documents/Arduino/libraries```.

3. A placa que deve ser selecionada na lista de placas na IDE é a "NodeMCU 1.0 (ESP12-E Module)"

## Execução

Antes de enviar o código para a placa, você deve configurar o SSID e a senha da sua rede Wi-Fi no sketch, localizados na variável ```cred``` declarada no início do código. Depois disso, basta enviar o código para a placa!


## Como funciona



## License

This project is licensed under the MIT License - see [LICENSE](LICENSE) for details
