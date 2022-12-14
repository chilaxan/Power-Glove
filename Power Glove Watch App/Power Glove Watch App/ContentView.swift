//
//  ContentView.swift
//  Power Glove Watch App
//
//  Created by Jordan Limor on 10/16/22.
//

import SwiftUI

struct ContentView: View {
    @State private var logStarting = false
     
       @ObservedObject var sensorLogger = SensorLogManager()
       
       var body: some View {
           VStack {
               Button(action: {
                   self.logStarting.toggle()
                   
                   if self.logStarting {
                       WKExtension.shared().isAutorotating = true
                       self.sensorLogger.startUpdate(50.0)
                   }
                   else {
                       self.sensorLogger.stopUpdate()
                       
                   }
               }) {
                   if self.logStarting {
                       Image(systemName: "pause.circle")
                   }
                   else {
                       Image(systemName: "play.circle")
                   }
               }
               
               VStack {
                   VStack {
                   Text("Accelerometer").font(.headline)
                   HStack {
                       Text(String(format: "%.2f", self.sensorLogger.accX))
                       Spacer()
                       Text(String(format: "%.2f", self.sensorLogger.accY))
                       Spacer()
                       Text(String(format: "%.2f", self.sensorLogger.accZ))
                   }.padding(.horizontal)
                   }
                   
                   VStack {
                   Text("Gyroscope").font(.headline)
                   HStack {
                       Text(String(format: "%.2f", self.sensorLogger.gyrX))
                       Spacer()
                       Text(String(format: "%.2f", self.sensorLogger.gyrX))
                       Spacer()
                       Text(String(format: "%.2f", self.sensorLogger.gyrX))
                   }.padding(.horizontal)
                   }

               }
           }
           
       }
}

struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        ContentView()
    }
}
