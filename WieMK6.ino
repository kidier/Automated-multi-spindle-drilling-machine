
//Program maszyny wiercącej wykonany na zlecenie firmy Trazni P.U.H. zrealizowany dnia 10.02.2021r.
//wykonawca Jakub Jurzak

int mode1 = 0; //1drill
int mode2 = 0; //2drill
int mode3 = 0; //3drill
int mode4 = 0; //press
int clck = 0; //stoper 1
int ps1 = 7; //1zawór
int ps2 = 8; //2zawór
int ps3 = 9; //3zawór
int ps4 = 6; //4zawór
int butt = 0; //przycisk 1
int hold = 0; //przycisk 2
int stat = 0; //status włączenia
int stat2 = 0; //status prytrzymania
int drill = 0; //wiercenie

void setup() 
{
  int in1 = digitalRead(A0);
  int in2 = digitalRead(A1);
  int in3 = digitalRead(A2);
  int in4 = digitalRead(A3);
  int in5 = digitalRead(2);
  int in6 = digitalRead(3);
  int butt = analogRead(A6);
  int hold = analogRead(A7);
  //start serial connection
  Serial.begin(9600);
  //pinMode(1, INPUT_PULLUP);
  pinMode(ps1, OUTPUT);
  pinMode(ps2, OUTPUT);
  pinMode(ps3, OUTPUT);
  pinMode(ps4, OUTPUT);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A7, INPUT);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  

  digitalWrite(ps1, LOW);
  digitalWrite(ps2, LOW);
  digitalWrite(ps3, LOW); 
  digitalWrite(ps4, LOW);

  Serial.println("Setup");
  delay(2500);
  
  Serial.println("Piston4 eject");
  digitalWrite(ps4, HIGH);
  delay(2000);
  digitalWrite(ps4, LOW);
  delay(500);
  
  Serial.println("Piston1 eject");
  digitalWrite(ps1, HIGH);
  delay(10000);
  in2 = digitalRead(A1);
  if(in2 == LOW)
  {
    digitalWrite(ps1, LOW);
  }
  else
  {
     stat = 4;
     return;
  }
  delay(500);
  
  Serial.println("Piston2 eject");
  digitalWrite(ps2, HIGH);
  delay(10000);
  in3 = digitalRead(A2);
  in4 = digitalRead(A3);
  if(in3 == LOW)
  {
    if(in4 == LOW)
    {
      digitalWrite(ps2, LOW);
    }
    else
    {
      stat = 4;
      return;
    }
  }
  else
  {
    stat = 4;
    return;
  }
  delay(500);
  
  Serial.println("Piston3 eject");
  digitalWrite(ps3, HIGH);
  delay(8000);
  in5 = digitalRead(2);
  in6 = digitalRead(3);
  if(in5 == LOW)
  {
    if(in6 == LOW)
    {
      digitalWrite(ps3, LOW);
    }
    else
    {
      stat = 4;
      return;
    }
  }
  delay(4000);
  Serial.println("All checked");  
      
     

  
  
  
}

void loop() 
{
  int in1 = digitalRead(A0);
  int in2 = digitalRead(A1);
  int in3 = digitalRead(A2);
  int in4 = digitalRead(A3);
  int in5 = digitalRead(2);
  int in6 = digitalRead(3);
  int butt = analogRead(A6);
  int hold = analogRead(A7);

//clock
  if(clck < 40)
  {        
    
    clck = clck + 1;
  }
  else
  {
    clck = 0;
  }
  


//Button state
  if(stat == 0)
  {
    if(butt > 50)    //w8 for push
    {
      stat = 1;
      drill = 1;
      clck = 0;
    }
  }
  if(stat == 1)
  {
    if(butt < 10)     //w8 for releas
    {
      stat = 2;
    }
  }
  if(stat == 2)
  {
    if(butt > 50)
    {
      stat = 3;
      drill = 0; 
    }
  }
  if(stat == 3)
  {
    if(butt < 50)
    {
      stat = 0;
    }
  }
  if(stat == 4)
  {
    Serial.print("ERROR");
  }



  // Drilling
  if(stat == 2)
  {
    //Neutrum
    if(mode1 == 0)
    {
      digitalWrite(ps1, LOW);
      //Serial.println("Setup1");
      //delay(100);
    }
    if(mode2 == 0)
    {
      digitalWrite(ps2, LOW);
      //Serial.println("Setup2");
      //delay(100);
    }
    if(mode3 == 0)
    {
      digitalWrite(ps3, LOW);
      //Serial.println("Setup3");
      //delay(100);
      //mode1 = 1;
      //mode2 = 1;
      //mode3 = 1;
    }
    



    


    //First Drill
    if(mode1 == 1) //first stage engage
    {
      if(in2 == HIGH)
      {
        if(in1 == HIGH)
        {
          digitalWrite(ps1, HIGH);
        }
        else
        {
          if(clck < 239)
          {
           digitalWrite(ps1, HIGH); 
          //Serial.println("drill1");
          }
          else
          {
           digitalWrite(ps1, LOW); 
          //Serial.println("drill1");
          }     
        }
         
      }
      else
      {
        delay(300);
        mode1 = 2;
         
      }
    }
    if(mode1 == 2) //first stage disengage
    {
      if(in1 == LOW)
      {
        digitalWrite(ps1, LOW);
        //Serial.println("NOdrill1");     
      }
      else
      {
        mode1 = 3;
      }
    }
    if(mode1 == 3) //first stage secund engage
    {
      if(in2 == HIGH)
      {
        if(clck < 239)
        {
          digitalWrite(ps1, HIGH); 
        //Serial.println("drill1");
        }
        else
        {
          digitalWrite(ps1, LOW); 
        //Serial.println("drill1");
        }
      }
      else
      {
        delay(1100);
        mode1 = 4;
      }
    }
    if(mode1 == 4) //first stage disengage
    {
      if(in1 == LOW)
      {
        digitalWrite(ps1, LOW);
        //Serial.println("NOdrill11");     
      }
      else
      {
        mode1 = 0;
      }
    }




    //Secound Drill
    if(mode2 == 1) //secound stage engage
    {
      if(in3 == HIGH)
      {
        digitalWrite(ps2, HIGH);
        //Serial.println("drill2");     
      }
      else
      {
        mode2 = 2;
      }
    }
    if(mode2 == 2) //secound stage disengage
    {
      if(in3 == LOW)
      {
        digitalWrite(ps2, LOW);
        //Serial.println("NOdrill2");     
      }
      else
      {
        //Serial.println("w8tin"); 
      }
    }
    if(mode2 == 3) //secound stage reengage
    {
      if(in4 == HIGH)
      {
        if(in3 == HIGH)
        {
          digitalWrite(ps2, HIGH); 
        }
        else
        {
          if(clck < 238)
          {
           digitalWrite(ps2, HIGH); 
         //Serial.println("drill1");
         }
         else
         {
           digitalWrite(ps2, LOW); 
         //Serial.println("drill1");
         }     
        }
      }
      else
      {
        delay(600);
        mode2 = 4;
      }
    }
    if(mode2 == 4) //secound stage redisengage
    {
      if(in3 == LOW)
      {
        digitalWrite(ps2, LOW);
        //Serial.println("NOdrill22");     
      }
      else
      {
        if(mode3 == 0)
        {
          if(mode1 == 0)
          {
            mode2 = 0;
            stat = 0;
          }
        }

      }
    }




    //Third Drill
    if(mode3 == 1) //third stage engage
    {
      if(in5 == HIGH)
      {
        digitalWrite(ps3, HIGH);
        //Serial.println("drill3");     
      }
      else
      {
        mode3 = 3; //skip 2 to mode 3 
      }
    }
    if(mode3 == 2) //third stage disengage
    {
      if(in5 == LOW)
      {
        digitalWrite(ps3, LOW);
        //Serial.println("NOdrill3");     
      }
      else
      {
        mode3 = 3;
      }
    }
    if(mode3 == 3) //third stage engage
    {
      if(in6 == HIGH)
      {
        digitalWrite(ps3, HIGH);
        //Serial.println("drill33");     
      }
      else
      {
        mode3 = 4;
      }
    }
    if(mode3 == 4) //third stage disengage
    {
      if(in5 == LOW)
      {
        digitalWrite(ps3, LOW);
        //Serial.println("NOdrill33");     
      }
      else
      {
        mode3 = 0;
        mode2 = 3;
      }
    }
  }
  else
  {
    digitalWrite(ps1, LOW);
    digitalWrite(ps2, LOW);
    digitalWrite(ps3, LOW);
    
    mode1 = 1;
    mode2 = 1;
    mode3 = 1;

    //Hold state
    if(stat2 == 0)
    {
      if(hold > 50)    //w8 for push
      {
        stat2 = 1; 
        digitalWrite(ps4, HIGH); 
      }
    }
    if(stat2 == 1)
    {
     if(hold < 10)     //w8 for releas
      {
        stat2 = 2;
      }
    }
    if(stat2 == 2)
    {
     if(hold > 50)
      {
        stat2 = 3;
        digitalWrite(ps4, LOW);
      }
    }
    if(stat2 == 3)
    {
      if(hold < 50)
      {
        stat2 = 0;
      }
    }
  }
  delay(26); 
  Serial.print("Status:");
  Serial.print(" "); 
  Serial.print(mode1);
  Serial.print(" ");
  Serial.print(mode2);
  Serial.print(" ");
  Serial.print(mode3);
  Serial.print(" B: ");
  Serial.print(stat);
  Serial.print(" C: ");
  Serial.print(clck);  
  Serial.println("  ");
}
