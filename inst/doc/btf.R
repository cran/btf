## ------------------------------------------------------------------------
library(btf)
fit <- btf(nhtemp, k=2, iter=2000)

## ---- fig.show='hold', fig.width=7, fig.height=5-------------------------
s2_sample <- getPost(fit, 's2')
plot(s2_sample)

## ------------------------------------------------------------------------
getPostEst(fit, 's2', est=mean)

## ---- fig.show='hold', fig.width=5, fig.height=5-------------------------
plot(fit)

