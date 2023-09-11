data <- read.table('./dataset.csv', header = TRUE,  sep = ';',  stringsAsFactors = FALSE)
# View(data)
# data$n.n <- as.factor(data$n.n)

data$group <- as.factor(data$group)
data$sex <- as.factor(data$sex)
data$internetParticipation <- as.factor(data$internetParticipation)

# str(data)
group_one <- subset(data, group == 1)
group_two <- subset(data, group == 2)

#print("FIRST GROUP")
#summary(group_one)

#print("SECOND GROUP")
#summary(group_two)

#library(psych)

#sm<-describe(group_one)
#sm2<-describe(group_two)
#View(sm)
#View(sm2)

# plot(data.frame(group_one$age, group_one$Quality))
# plot(data.frame(group_two$age, group_two$Quality))

#x<-c(summary(data$sex))
#piepercent<- round(100*x/sum(x), 1)
#pie(x, piepercent, radius=1, main="ОЧЕНь радикальная диаграмма", xlab="название оси X", ylab="название оси Y", col=c("red", "blue", "green", "brown"), clockwise=TRUE)
#legend("topright", c("One","Two", "Three", "Four"), cex = 0.8, fill =c("red", "blue", "green", "brown"))

M <- data[,unlist(lapply(data, is.numeric))]
N1<-cor(M,use="pairwise.complete.obs")

library("corrplot")
col <- colorRampPalette(c("#BB4444", "#EE9988", "#FFFFFF", "#77AADD",
                            "#4477AA"))
corrplot(N1, method="color", col=NULL,
           type="upper", order="hclust",
           addCoef.col = "black", tl.col="black", tl.srt=45,
           sig.level = 0.01, insig = "blank",
           diag=FALSE
)

a<-cor.test(data$Quality, data$averagePagesPerVisit)
# print(a)

hist(data$averagePrice)

b <- fisher.test(table(data$sex, data$internetParticipation))
print(b)
# system('read -p "Press [Enter] key to end..."')
