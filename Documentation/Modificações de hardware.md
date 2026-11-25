
O sistema do trator passou por algumas modificações necessárias para melhoria do sistema e integração dos sensores para o sensoriamento do mesmo.

---
## Antes:

O sistema anterior contava com um Arduino Mega 2560, o cérebro do trator, um Arduino Mini que é responsável pelo controle dos drives que consequentemente controlam os motores com o auxilio de uma Ponte H para a movimentação do trator e um regulador de tensão para integração do sistema.

![[Pasted image 20261125143704.png|209]]

---
## Depois:

Nesta atualização do trator, foi feita a adição de alguns componentes como um EPS32 para a comunicação wi-fi do projeto. Um divisor de tensão desenvolvido com resistores para a regulação da tensão, a fim de reduzir a tensão de 5V enviada pelo pino TX do Arduino para que o ESP32 consiga efetuar a leitura com segurança. Além disso, puxamos uma trilha de 5V para aumentar a quantidade de pinos disponíveis para a alimentação dos sensores.

| ![[Pasted image 20261125143739.png\|300]] | ![[Pasted image 20261125143758.png\|233]] |
| ----------------------------------------- | ----------------------------------------- |

Para o sensoriamento, tivemos diversos sensores implementados ao trator: 
RFID RC522, GPS, DHT22, BMP280

---