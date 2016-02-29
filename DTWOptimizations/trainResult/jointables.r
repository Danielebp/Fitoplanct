#path<-"~/git/Fitoplanct/DTWOptimizations";
#setwd(path)

nomes<- c('BtIso','ChaetocerosGracilis','ChaetocerosTennueCB','Chlamidomonas','Chlorela','Chloroficea','Chromonas','CiliadoRosaCB','CP','Isochrysis','Microcystis','Nanocloris','Navicula','Odontela','PhormidiumCB','Platymonas','Prasinoficeae','Skletonema','T_T','Talassiosira','TS','VA_52');


nesp<-22

for(i in 1:nesp){
  for(j in i:nesp){
    name<-paste("result_",i,"_",j,".csv",sep="")
    var<-paste("r_",i,"_",j,sep="")
    assign(var,read.csv(name, header = FALSE))
  }
}

for(i in 1:nesp){
   for(j in 1:nesp){
     if(j<i){
       var<-paste("r_",j,"_",i,sep="");
       
       if(j==1){
 l<-t(get(var));
       }
       else{
 l<-cbind(l, t(get(var)));
       }
       
     }
     else{
       var<-paste("r_",i,"_",j,sep="");
       
       if(j==1){
 l<-get(var);
       }
       else{
 l<-cbind(l, get(var));
       }
     }
   }
   names(l)<-c(1:dim(l)[2])
   
   l<-cbind(l, c(rep(nomes[i], dim(l)[1])))
     
   if(i==1){
     m<-l;
   }
   else{
     m<-rbind(m, l);
   }
 }

write.csv(m, "tabela22esp.csv", row.names=FALSE)

