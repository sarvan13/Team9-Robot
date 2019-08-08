//   if(side_state == LEFT_SIDE){
//     if(progress == RAMP_STATE){
//       for(int i = 0; i < 2; i++){
//         while(tape_detection.branch_exists() == NO_BRANCH || tape_detection.branch_side == RIGHT_BRANCH)
//         {
//           movement.apply_pid(tape_detection.get_pid());
//         }
//         if(tape_detection.branch_side == LEFT_BRANCH) {
//           Serial.println("left branch detected");
//           movement.stop();
//           delay(200);
//           movement.turn_left();
//           delay(200);
//           while(abs(tape_detection.get_path_error()) >= 4){

//           }
//           for(int i = 0; i < 100; i++){
//             movement.apply_pid(tape_detection.get_pid());
//           }
//         }
//       }
//     progress = NORMAL;
//     } else if(progress == NORMAL){
//         for(int i = 0; i < 2; i++){
//           if(i == 1){
//             movement.set_speed(80);
//             tape_detection.set_Kd(0);
//             tape_detection.set_Kp(18);
//           }
//           while(tape_detection.marker_exists() == NO_MARKER){
//             movement.apply_pid(tape_detection.get_pid());
//           }
//           movement.stop();
//           delay(200);
//           while(tape_detection.marker_exists() == NO_MARKER){
//             if(i == 0){
//               movement.reverse(100,80);
//             }else{
//               movement.reverse(80,80);
//             }
//           }
//           delay(100);
//           movement.stop();
//           delay(40);
//           position_arm_left();
//           delay(300);
//           while(digitalRead(IN)){

//           }
//           if(tape_detection.marker_side == LEFT_MARKER){
//             // movement.set_speed(500);
//             // tape_detection.set_Kp(120);
//             // tape_detection.set_Kd(25);
//             if(i==0){
//               for(int i = 0; i< 800; i++){
//                 movement.apply_pid(tape_detection.get_pid());
//               }
//             }

//           }

//       }
//       progress = GAUNTLET;
//     }else if(progress == GAUNTLET){
//       movement.rotate_right(90);
//       delay(500);
//       while(abs(tape_detection.get_path_error()) >=4){

//       }
//       movement.set_speed(140);
//       tape_detection.set_Kp(30);
//       tape_detection.set_Kd(0);
//       for(int i = 0; i < 2; i++){
//         while(tape_detection.branch_exists() == NO_BRANCH || tape_detection.branch_side == RIGHT_BRANCH)
//         {
//           if(tape_detection.branch_side == RIGHT_BRANCH && i == 0){
//             // movement.set_speed(500);
//             // tape_detection.set_Kp(125);
//             // tape_detection.set_Kd(25);
//           }
//           movement.apply_pid(tape_detection.get_pid());
//         }
//         if(tape_detection.branch_side == LEFT_BRANCH){
//           movement.stop();
//           delay(300);
//         }
//         if(i == 0){
//           movement.set_speed(140);
//           tape_detection.set_Kp(30);
//           tape_detection.set_Kd(10);
//           for(int i = 0; i< 100; i++){
//             movement.apply_pid(tape_detection.get_pid());
//           }
//         }

//       }

//       movement.turn_left();
//       delay(100);
//       while(abs(tape_detection.get_path_error()) >=4){

//       }
//       for(int i = 0; i < 500; i++){
//         movement.apply_pid(tape_detection.get_pid());
//       }
//       movement.rotate_right(80);
//       delay(4000);
//       while(abs(tape_detection.get_path_error()) >=4){

//       }
//       movement.set_speed(150);
//       tape_detection.set_Kp(30);
//       tape_detection.set_Kd(0);
//       // while(abs(tape_detection.get_alternate_path_error()) >=0){
//       //   movement.apply_pid(tape_detection.get_pid());
//       // }

//       for(int i = 0; i < 2200; i++){
//         movement.apply_pid(tape_detection.get_pid());
//       }
//       // movement.stop();
//       // delay(1000);
//       // movement.reverse(100,100);
//       // delay(3000);
//       // movement.stop();
//       // movement.turn_right();
//       // while(abs(tape_detection.get_path_error()) > 4)
//       movement.set_speed(100);
//       tape_detection.set_Kp(40);
//       tape_detection.set_Kd(0);
//       for(int i = 0; i < 10000; i++){
//         movement.alternate_pid(tape_detection.alternate_get_pid());
//       }
//       movement.stop();
//       drop_stone_gauntlet();
//       delay(300);
//       while(digitalRead(IN)){

//       }
//       progress = STOP;
//     } else if(progress == STOP){
//       movement.stop();
//     }
//   }
// else{
//   if (progress == RAMP_STATE)
//   {
//     for (int i = 0; i < 2; i++)
//     {
//       while (tape_detection.branch_exists() == NO_BRANCH || tape_detection.branch_side == LEFT_BRANCH)
//       {
//         movement.apply_pid(tape_detection.get_pid());
//       }
//       if (tape_detection.branch_side == RIGHT_BRANCH)
//       {
//         Serial.println("left branch detected");
//         movement.stop();
//         delay(200);
//         movement.turn_right();
//         delay(200);
//         while (abs(tape_detection.get_path_error()) >= 4)
//         {
//         }
//         for (int i = 0; i < 500; i++)
//         {
//           movement.apply_pid(tape_detection.get_pid());
//         }
//       }
//     }
//     progress = NORMAL;
//   }
//   else if (progress == NORMAL)
//   {
//     for (int i = 0; i < 2; i++)
//     {
//       if (i == 1)
//       {
//         movement.set_speed(80);
//         tape_detection.set_Kd(5);
//         tape_detection.set_Kp(18);
//       }
//       while (tape_detection.marker_exists() == NO_MARKER)
//       {
//         movement.apply_pid(tape_detection.get_pid());
//       }
//       movement.stop();
//       delay(200);
//       while (tape_detection.marker_exists() == NO_MARKER)
//       {
//         if (i == 0)
//         {
//           movement.reverse(80, 100);
//         }
//         else
//         {
//           movement.reverse(80, 80);
//         }
//       }
//       delay(100);
//       movement.stop();
//       delay(40);
//       position_arm_right();
//       delay(300);
//       while(digitalRead(IN)){

//       }
//       if (tape_detection.marker_side == RIGHT_MARKER)
//       {
//         movement.set_speed(500);
//         tape_detection.set_Kp(120);
//         tape_detection.set_Kd(25);
//         if (i == 0)
//         {
//           for (int i = 0; i < 800; i++)
//           {
//             movement.apply_pid(tape_detection.get_pid());
//           }
//         }
//       }
//     }
//     progress = GAUNTLET;
//   }
//   else if (progress == GAUNTLET)
//   {
//     movement.rotate_left(90);
//     delay(500);
//     while (abs(tape_detection.get_path_error()) >= 4)
//     {
//     }
//     movement.set_speed(140);
//     tape_detection.set_Kp(30);
//     tape_detection.set_Kd(15);
//     for (int i = 0; i < 2; i++)
//     {
//       while (tape_detection.branch_exists() == NO_BRANCH || tape_detection.branch_side == LEFT_BRANCH)
//       {
//         if (tape_detection.branch_side == RIGHT_BRANCH && i == 0)
//         {
//           // movement.set_speed(500);
//           // tape_detection.set_Kp(125);
//           // tape_detection.set_Kd(25);
//         }
//         movement.apply_pid(tape_detection.get_pid());
//       }
//       if (tape_detection.branch_side == RIGHT_BRANCH)
//       {
//         movement.stop();
//         delay(300);
//       }
//       if (i == 0)
//       {
//         movement.set_speed(140);
//         tape_detection.set_Kp(30);
//         tape_detection.set_Kd(10);
//         for (int i = 0; i < 100; i++)
//         {
//           movement.apply_pid(tape_detection.get_pid());
//         }
//       }
//     }
//     for(int i = 0; i < 1500; i++){
//       movement.apply_pid(tape_detection.get_pid());
//     }
//     movement.turn_right();
//     delay(100);
//     while (abs(tape_detection.get_path_error()) >= 4)
//     {}
//     for(int i = 0; i < 300; i++){
//       movement.apply_pid(tape_detection.get_pid());
//     }
//     movement.rotate_left(80);
//     delay(4000);
//     while (abs(tape_detection.get_path_error()) >= 4)
//     {}
//     movement.set_speed(150);
//     tape_detection.set_Kp(30);
//     tape_detection.set_Kd(0);
//     // while(abs(tape_detection.get_alternate_path_error()) >=0){
//     //   movement.apply_pid(tape_detection.get_pid());
//     // }

//     for (int i = 0; i < 2000; i++)
//     {
//       movement.apply_pid(tape_detection.get_pid());
//     }
//     // movement.stop();
//     // delay(1000);
//     // movement.reverse(100,100);
//     // delay(3000);
//     // movement.stop();
//     // movement.turn_right();
//     // while(abs(tape_detection.get_path_error()) > 4)
//     movement.set_speed(100);
//     tape_detection.set_Kp(40);
//     tape_detection.set_Kd(0);
//     for (int i = 0; i < 2000; i++)
//     {
//       movement.alternate_pid(tape_detection.alternate_get_pid());
//     }

//     movement.stop();
//     drop_stone_gauntlet();
//     delay(300);
//     while(digitalRead(IN)){
        
//     }
//     progress = STOP;
//   }
//   else if (progress == STOP)
//   {
//     movement.stop();
//   }
// }