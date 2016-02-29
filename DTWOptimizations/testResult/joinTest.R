#path<-"~/git/Fitoplanct/DTWOptimizations/testResult";
#setwd(path)


nomes<- c('BtIso','ChaetocerosGracilis','ChaetocerosTennueCB','Chlamidomonas','Chlorela','Chloroficea','Chromonas','CiliadoRosaCB','CP','Isochrysis','Microcystis','Nanocloris','Navicula','Odontela','PhormidiumCB','Platymonas','Prasinoficeae','Skletonema','T_T','Talassiosira','TS','VA_52');

nEsp<-22;

#vazios<-c(3,8,10,13,16,18,20,21)
#esps<- setdiff(1:22, vazios)
esps<- 1:nEsp

for(i in esps){
  for(j in 1:nEsp){
    name<-paste("test_result_",i,"_",j,".csv",sep="")
    var<-paste("r_",i,"_",j,sep="")
    assign(var,read.csv(name, header = FALSE))
  }
}

for(i in esps){
   for(j in 1:nEsp){
     var<-paste("r_",i,"_",j,sep="");
       
       if(j==1){
	l<-get(var);
       }
       else{
	l<-cbind(l, get(var));
       }
     
   }
   names(l)<-c(1:dim(l)[2])
   
   l<-cbind(l, c(rep(nomes[i], dim(l)[1])))
   
   write.csv(l, paste("result",nomes[i],".csv", sep=""), row.names=FALSE)
   
 }



