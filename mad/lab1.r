install.packages("psych")
install.packages("BiocManager")
BiocManager::install("graph")
install.packages("ggm")
install.packages("corrplot")

library(ggm)
library(psych)
library(corrplot)

data <- read.table('./dataset.csv',
                   header = TRUE,
                   sep = ',',
                   stringsAsFactors = FALSE
)

View(data)

data$group <- as.factor(data$group)
data$sex <- as.factor(data$sex)
data$participationInSurveys <- as.factor(data$participationInSurveys)
data$satisfactionDegree <- as.factor(data$satisfactionDegree)

str(data)
group_one <- subset(data, group == 1)
group_two <- subset(data, group == 2)

summary(data)
summary(group_one)
summary(group_two)

base_stats <- function(x) {
  if(is.numeric(x)) {
    s<-sd(x)
    m<-mean(x)
    n<-length(x)
    skew<-sum((x-m)^3/s^3)/n
    kurt<-sum((x-m)^4/s^4)/n-3
    uniqv<-unique(x)
    View (c(sd=s,skew=skew,kurtosis=kurt,mode=uniqv[which.max(tabulate(match(x,uniqv)))]))
  }
}

describe_builder <- function(data) {
  sm <- describe(data)
  View(sm)
}

plot_builder <- function(column_one, column_two, main, xlab, ylab) {
  plot(data.frame(column_one, column_two),
       pch = 16,
       main = main,
       xlab = xlab,
       ylab = ylab
  )
}

pie_builder <- function(table_row, main, colors, descr_colors) {
  summarized <- c(summary(table_row))
  piepercent <- round(100 * summarized / sum(summarized), 1)

  pie(summarized,
      piepercent,
      radius = 0.75,
      main = main,
      col = colors,
      clockwise = TRUE
  )

  legend("topright", descr_colors, cex = 1.5, fill = colors)
}

barplot_builder <- function(table_row, main) {
  barplot(table(table_row),
          main = main,
          border = "red",
          col = "blue",
          density = 10
  )
}

boxplot_builder <- function(table_row_k, table_row_n, xlab, ylab, data) {
  boxplot(table_row_n ~ table_row_k,
          xlab = xlab,
          ylab = ylab,
          col = "#AACCFF",
          data = data
  )
}

chisq_builder <- function(data) {
  factor_names <- names(data[,unlist(lapply(data, is.factor))])

  chi_results <- matrix(NA,
                        nrow = length(factor_names),
                        ncol = length(factor_names)
  )

  colnames(chi_results) <- c(factor_names)
  rownames(chi_results) <- c(factor_names)

  for (col_name in factor_names){
    for (col_name2 in factor_names) {
      if (col_name == 'group' || col_name == col_name2 || col_name2 == 'group') next
      chi_results[col_name,col_name2] <- chisq.test(table(data[,col_name],data[,col_name2]))$p.value
    } 
  }

  View(chi_results)
}

fisher_builder <- function(data) {
  factor_names <- names(data[,unlist(lapply(data, is.factor))])
  
  fisher_results <- matrix(NA,
                        nrow = length(factor_names),
                        ncol = length(factor_names)
  )
  
  colnames(fisher_results) <- c(factor_names)
  rownames(fisher_results) <- c(factor_names)
  
  for (col_name in factor_names){
    for (col_name2 in factor_names) {
      if (col_name == 'group' || col_name == col_name2 || col_name2 == 'group') next
      fisher_results[col_name, col_name2] <- fisher.test(table(data[,col_name], data[,col_name2]))$p.value
    } 
  }
  
  View(fisher_results)
}

cor_builder <- function(data) {
  M <- data[,unlist(lapply(data, is.numeric))]

  N1 <- cor(M,use="pairwise.complete.obs")
  N2 <- cor(M,use="pairwise.complete.obs",method="spearman")
  N3 <- cor(M,use="pairwise.complete.obs",method="kendall")

  print("General")
  print(N1)
  print("Spearman")
  print(N2)
  print("Kendall")
  print(N3)
}

pcor_builder <- function(data, depend) {
  M <- data[,unlist(lapply(data, is.numeric))]
  pcor(depend, cov(M))
}

corrplot_builder <- function(data, colors) {
  M <- data[,unlist(lapply(data, is.numeric))]
  N1 <- cor(M, use="pairwise.complete.obs")
  
  col <- colorRampPalette(colors)
  corrplot(N1, method="color", col=NULL,  
             type="upper", order="hclust", 
             addCoef.col = "black", tl.col="black", tl.srt=45,
             sig.level = 0.01, insig = "blank",
             diag=FALSE 
  )
}

base_stats(data$age)
base_stats(data$purchasesYearly)
base_stats(data$averagePurchasesPrice)
base_stats(data$averagePagesPerVisit)
base_stats(data$supportRequestYearly)
base_stats(data$satisfactionRate)

base_stats(group_one$age)
base_stats(group_one$purchasesYearly)
base_stats(group_one$averagePurchasesPrice)
base_stats(group_one$averagePagesPerVisit)
base_stats(group_one$supportRequestYearly)
base_stats(group_one$satisfactionRate)

base_stats(group_two$age)
base_stats(group_two$purchasesYearly)
base_stats(group_two$averagePurchasesPrice)
base_stats(group_two$averagePagesPerVisit)
base_stats(group_two$supportRequestYearly)
base_stats(group_two$satisfactionRate)

describe_builder(data)
describe_builder(group_one)
describe_builder(group_two)

plot_builder(group_one$averagePagesPerVisit, group_one$satisfactionRate,
             "Диаграмма рассеяния", "Средняя посещаемость страниц",
             "Удовлетворенность услугами"
)

plot_builder(group_two$averagePagesPerVisit, group_two$satisfactionRate,
             "Диаграмма рассеяния", "Средняя посещаемость страниц",
             "Удовлетворенность услугами"
)

pie_builder(group_one$satisfactionDegree,
            "Распределение по удовлетворенности услугами",
            c("#AAFFCC", "#FFAACC", "#AACCFF"),
            c("average", "high", "low")
)

pie_builder(group_two$satisfactionDegree,
            "Распределение по удовлетворенности услугами",
            c("#AAFFCC", "#FFAACC", "#AACCFF"),
            c("average", "high", "low")
)

barplot_builder(group_one$satisfactionDegree, "Степень удовлетворенности услугами")
barplot_builder(group_two$satisfactionDegree, "Степень удовлетворенности услугами")

boxplot_builder(group_one$sex, group_one$satisfactionRate, "s", "a", group_one)
boxplot_builder(group_two$sex, group_two$satisfactionRate, "s", "a", group_two)

hist(data$purchasesYearly, freq=FALSE, breaks=20, col = "#AACCFF", xlab="x", ylab="y", main="main")
lines(density(data$satisfactionRate))

pairs(~data$age + data$purchasesYearly + data$averagePurchasesPrice
      + data$averagePagesPerVisit + data$averagePagesPerVisit
      + data$satisfactionRate,
      lower.panel = NULL
)

chisq_builder(group_one)
chisq_builder(group_two)

fisher_builder(group_one)
fisher_builder(group_two)

aov_model <- aov(group_one$purchasesYearly ~ group_one$sex, group_one = group_one)
summary(aov_model)

cor_builder(group_one)
cor_builder(group_two)

pcor_builder(group_one, c(3, 4, 5))
corrplot_builder(group_one, c("#BB4444", "#EE9988", "#FFFFFF", "#77AADD", "#4477AA"))

cor.test(group_one$purchasesYearly, group_one$age)
