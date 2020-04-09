#include <SPI.h>
#include <MFRC522.h>
 
const int resetPin = 22; // Reset pin
const int ssPin = 21;    // Slave select pin
 
MFRC522 mfrc522 = MFRC522(ssPin, resetPin); // Create instance
 
void setup() {
  Serial.begin(115200);
  SPI.begin();   
 
  mfrc522.PCD_Init();
  Serial.println("RFID + ESP32");
  Serial.println("Aguardando tag RFID para verificar o id da mesma.");
  delay(1000);
 
}
 
void loop() {
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
     return;                 // se nao tiver um cartao para ser lido recomeça o void loop
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;                  //se nao conseguir ler o cartao recomeça o void loop tambem
  }
  String conteudo = "";      // cria uma string
 
  Serial.print("id da tag :"); //imprime na serial o id do cartao
 
  for (byte i = 0; i < mfrc522.uid.size; i++){       // faz uma verificacao dos bits da memoria do cartao
     //ambos comandos abaixo vão concatenar as informacoes do cartao...
     //porem os 2 primeiros irao mostrar na serial e os 2 ultimos guardarao os valores na string de conteudo para fazer as verificacoes
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     conteudo.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     conteudo.concat(String(mfrc522.uid.uidByte[i], HEX));
     
     }
     Serial.println();

     Serial.print("COncat");
     Serial.println(conteudo);
     delay(5000);
  }
