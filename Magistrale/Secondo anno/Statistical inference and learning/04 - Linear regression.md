Regression models the **conditional mean** of a response $Y$ given predictors $\mathbf{X}$:
$$\mathbb{E}(Y \mid \mathbf{X}=\mathbf{x}) = m(\mathbf{x}).$$

It has two goals that overlap but differ:
- **Explanation**: how does the average of $Y$ change with $X$?
- **Prediction**: estimate an unknown or future $Y$ at given $x$ values

Let's use as an example, the `cars` dataset: $Y_i$ is stopping distance and $x_i$ is speed, with sample correlation $0.807$, before fitting, we should ask ourselves **four questions**:
- Is the relationship roughly linear?
- Is the vertical spread constant?
- Are there unusual points?
- Is extrapolating outside the observed range defensible?

#### Simple linear regression model
$$Y_i = \beta_0 + \beta_1 x_i + \varepsilon_i, \qquad i=1,\dots,n$$
- $\beta_0$ is the intercept, the mean of $Y$ at $x=0$
- $\beta_1$ is the slope, the change in mean $Y$ per one-unit increase in $x$
- $\varepsilon_i$ is the random error, the deviation from the conditional mean

**Assumptions** (conditional on $\mathbf{X}$):
$$\mathbb{E}(\varepsilon_i\mid\mathbf X)=0,\quad \operatorname{Var}(\varepsilon_i\mid\mathbf X)=\sigma^2,\quad \operatorname{Cov}(\varepsilon_i,\varepsilon_j\mid\mathbf X)=0\ (i\ne j).$$

In words: errors are centered at zero, have constant variance (i.e. _homoscedasticity_), and are uncorrelated, it follows that $\mathbb{E}(Y_i\mid x_i)=\beta_0+\beta_1x_i$ and $\operatorname{Var}(Y_i\mid x_i)=\sigma^2$.

"Linear" means **linear in the coefficients, not in $x$.**
- Linear: $\beta_0+\beta_1x+\beta_2x^2$ and $\beta_0+\beta_1\log x$.
- Not linear: $\beta_0+\exp(\beta_1 x)$.

The intercept may be meaningless if $x=0$ is impossible or far from the data. Centering ($x^*=x-\bar x$) makes $\beta_0$ the mean response at the average $x$.

#### Ordinary least squares (OLS)
OLS picks the line minimizing the **residual sum of squares**:
$$\mathrm{RSS}(b_0,b_1)=\sum_{i=1}^n (y_i-b_0-b_1x_i)^2,\qquad (\hat\beta_0,\hat\beta_1)=\arg\min_{b_0,b_1}\mathrm{RSS}$$
Setting both partial derivatives to zero gives the **normal equations**, with:
$$S_{xx}=\sum_i (x_i-\bar x)^2,\qquad S_{xy}=\sum_i (x_i-\bar x)(y_i-\bar y)$$
- $S_{xx}$ measures how spread out the $x$'s are
- $S_{xy}$ measures how $x$ and $y$ move together, its sign gives the direction of the association

The solution to the optimization problem, that is: <u>finding the straight line that best fits the observed data points by minimizing the sum of squared prediction errors</u> is:
$$\hat\beta_1=\frac{S_{xy}}{S_{xx}},\qquad \hat\beta_0=\bar y-\hat\beta_1\bar x$$
>The fitted line always passes through $(\bar x,\bar y)$.

**Least squares = Gaussian maximum likelihood**
If $\varepsilon_i\overset{iid}{\sim}\mathcal N(0,\sigma^2)$, the log-likelihood is:
$$\ell(\beta_0,\beta_1,\sigma^2)=-\frac n2\log\sigma^2-\frac1{2\sigma^2}\sum_i (y_i-\beta_0-\beta_1x_i)^2$$
For fixed $\sigma^2$, the coefficients enter only through the last term, which is $-\mathrm{RSS}/(2\sigma^2)$.
Maximizing $\ell$ is therefore the same as minimizing RSS, so MLE = OLS for $\beta$. 

Maximizing over $\sigma^2$ too gives $\hat\sigma^2_{ML}=\mathrm{RSS}/n$, which is biased downward, the unbiased version divides by $n-p$.

**Numerical minimization (`optim`)**
$Q(b_0,b_1)=\mathrm{RSS}$ is a [[01 - Convexity#Convex functions|convex]] quadratic when $S_{xx}>0$, so it has a unique global minimum, and `optim(method="BFGS")` reproduces the closed form up to numerical tolerance.

**Fitted values and residuals**
$$\hat y_i=\hat\beta_0+\hat\beta_1x_i,\qquad e_i=y_i-\hat y_i$$
With an intercept, the normal equations imply $\sum e_i=0$ and $\sum x_ie_i=0$, residuals are orthogonal to the predictors.
>In R, `lm(dist ~ speed, data = cars)` gives the same estimates, the formula means "model the mean of `dist` with an intercept and `speed`".

---
### Sampling theory and inference

#### Variance and standard errors
Under homoscedastic (uncorrelated errors with $Var(\epsilon_i ∣ X) = \sigma^2$), the sampling variances of the two coefficients are:
$$  
\operatorname{Var}(\hat\beta_1\mid\mathbf X)=\frac{\sigma^2}{S_{xx}},\qquad  
\operatorname{Var}(\hat\beta_0\mid\mathbf X)=\sigma^2\Big(\frac1n+\frac{\bar x^2}{S_{xx}}\Big)  
$$

A wider spread of $x$ means a larger $S_{xx}$ and a more precise slope, repeated nearly identical $x$ values give little information about the slope.

$\sigma^2$ is unknown and is estimated by
$$s^2=\hat\sigma^2=\frac{\mathrm{RSS}}{n-p}$$
where $p$ is the number of estimated coefficients ($p=2$ in simple regression).

The $n-p$ denominator, the **residual degrees of freedom**, makes the estimator unbiased, the **residual standard error** is $s=\sqrt{s^2}$.

Plugging in $s$ gives:
$$\widehat{se}(\hat\beta_1)=\frac{s}{\sqrt{S_{xx}}},\qquad \widehat{se}(\hat\beta_0)=s\sqrt{\frac1n+\frac{\bar x^2}{S_{xx}}}$$

#### Tests and confidence intervals
If the errors ($\epsilon_i\sim N(0,\sigma^2)$) are independent Gaussian variables, then:
$$\frac{\hat\beta_j-\beta_j}{\widehat{se}(\hat\beta_j)}\sim t_{n-2}\qquad j=0,1$$
>Without Gaussian errors this holds only approximately in large samples.

**Testing**
In some situations we are interested in performing hypothesis testing on a regression coefficient
$$H_0:\beta_j=b_{j,0}\quad vs\quad H_1:\beta_j\neq b_{j,0}$$

Where the assumed distribution for the null hypothesis $H_0$ is $T_j=(\hat\beta_j-b_{j,0})/\widehat{se}(\hat\beta_j)\sim t_{n-2}$.

In particular, to evaluate whether a given predictor influences the conditional mean of $Y$ , it is necessary to test whether the related coefficient $\beta_j$ is equal to zero.
$$H_0:\beta_j=0\quad vs\quad H_1:\beta_j\neq0$$
>For the common test of no linear association, $H_0:\beta_1=)$.

A two-sided $(1 − \alpha)$ **confidence interval** is
$$\hat\beta_j\pm t_{1-\alpha/2,\,n-2}\,\widehat{se}(\hat\beta_j).$$

#### Decomposing variability, $R^2$ and the F-test
Considering a simple linear regression model with an intercept, we can have the following decomposition:
$$\underbrace{\sum(y_i-\bar y)^2}_{\text{TSS (total)}}=\underbrace{\sum(\hat y_i-\bar y)^2}_{\text{RegSS (explained)}}+\underbrace{\sum(y_i-\hat y_i)^2}_{\text{RSS (unexplained)}}$$ $$R^2=\frac{\mathrm{RegSS}}{\mathrm{TSS}}=1-\frac{\mathrm{RSS}}{\mathrm{TSS}} .$$
$R^2$ is the in-sample fraction of variation in $y$ explained by the model.
```r
TSS <- sum((y - mean(y))^2)
RegSS <- sum((fitted(fit_cars) - mean(y))^2)
RSS <- sum((y - fitted(fit_cars))^2)
c(TSS=TSS,
	RegSS=RegSS,
	RSS=RSS,
	R_squared = 1 - RSS / TSS
)
```

svg trieste
**Overall F-test** (in simple regression it is equivalent to the t-test for $\beta_1$):
$$F=\frac{\mathrm{RegSS}/1}{\mathrm{RSS}/(n-2)}\sim F_{1,n-2}\text{ under }H_0:\beta_1=0 .$$

It corresponds to the **analysis of variance (ANOVA)** table in `anova()`.
>See [analysis of variance](https://en.wikipedia.org/wiki/Analysis_of_variance).

#### Mean response vs new observation
At a new value $x_0$, the estimated mean is $\mathbb E[Y|X=x_0]=\hat Y_0=\hat\beta_0+\hat\beta_1x_0$.

**Confidence interval for the mean response**:
$$\hat Y_0\pm t_{n-2,1-\alpha/2}\; s\sqrt{\frac1n+\frac{(x_0-\bar x)^2}{S_{xx}}}$$

**Prediction interval for a new response** $Y_0=\beta_0+\beta_1x_0+\varepsilon$:
$$\hat Y_0\pm t_{n-2,1-\alpha/2}\; s\sqrt{1+\frac1n+\frac{(x_0-\bar x)^2}{S_{xx}}}$$

Both intervals are narrowest at $\bar x$ and widen as $x_0$ moves away from the center of the data.

![[LR fitted mean and CI intervals.png|534]]

The prediction interval is always wider because it adds the irreducible noise $\varepsilon$ (the "1" under the root) on top of the uncertainty in the estimated mean.

---
### Multiple regression and model specification
#### Matrix form
With $p-1$ predictors (so $p$ coefficients including the intercept):
$$\mathbf Y=\mathbf X\boldsymbol\beta+\boldsymbol\varepsilon,\qquad \mathbb E(\boldsymbol\varepsilon\mid\mathbf X)=\mathbf 0,\quad \operatorname{Var}(\boldsymbol\varepsilon\mid\mathbf X)=\sigma^2\mathbf I_n$$

- $\mathbf X$ is the $n\times p$ **design matrix** (first column all ones)
- $\mathbf I_n$ is the identity matrix, meaning equal variances and no correlations
- For exact t and F inference, also assume $\boldsymbol\varepsilon\mid\mathbf X\sim\mathcal N_n(\mathbf 0,\sigma^2\mathbf I_n)$
- $\mathbf X$ must have **full column rank**: $p<n$ and no exact linear dependency among columns

The **OLS** estimator minimizes $RSS(b)=(\mathbf y-\mathbf X\mathbf b)^\top(\mathbf y-\mathbf X\mathbf b)$, this gives the normal equations $\mathbf X^\top\mathbf X\hat{\boldsymbol\beta}=\mathbf X^\top\mathbf Y$, so:
$$\hat{\boldsymbol\beta}=(\mathbf X^\top\mathbf X)^{-1}\mathbf X^\top\mathbf Y$$

**Sampling properties**
Since $\hat{\boldsymbol\beta}=\boldsymbol\beta+(\mathbf X^\top\mathbf X)^{-1}\mathbf X^\top\boldsymbol\varepsilon$, we obtain:
$$\mathbb E(\hat{\boldsymbol\beta}\mid\mathbf X)=\boldsymbol\beta,\qquad \operatorname{Var}(\hat{\boldsymbol\beta}\mid\mathbf X)=\sigma^2(\mathbf X^\top\mathbf X)^{-1}.$$

The diagonal of this matrix holds the variances of the coefficients and the off-diagonal entries hold their covariances.

Under the [Gauss–Markov assumptions](https://en.wikipedia.org/wiki/Gauss%E2%80%93Markov_theorem) OLS is **BLUE** (Best Linear Ubiased Estimator), meaning it has the smallest covariance matrix among linear estimators that are unbiased.

>[!Tip] Partial-effect interpretation
>In $\mathbb E(Y\mid X_1,X_2)=\beta_0+\beta_1X_1+\beta_2X_2$, we highlight the fact that $\beta_1$ is the difference in mean $Y$ for a one-unit increase in $X_1$ _holding $X_2$ fixed_.
>>This differs from the slope in a simple regression on $X_1$ alone.

#### F-tests in multiple regression
The **overall null** (intercept only) model is: $H_0:\beta_1=\dots=\beta_{p-1}=0$, where $p$ is the number of tested coefficient $+1$ (the intercept $\beta_0$), the statistic is:
$$F=\frac{\mathrm{RegSS}/(p-1)}{\mathrm{RSS}/(n-p)}\sim F_{p-1,\,n-p}$$
>Rejecting is equal to saying that at least one slope is nonzero, not which one.

**Nested models**
To compare a _reduced model_ ($R$) which excludes one or more explanatory variables against a _full model_ ($F$) which has every explanatory variable containing it:
$$F=\frac{(\mathrm{RSS}_R-\mathrm{RSS}_F)/(\text{number of extra parameters})}{\mathrm{RSS}_F/(n-p_F)}$$

#### Adjusted $R^2$
$R^2$ never decreases when adding predictors, even useless ones, adjusted $R^2$ penalizes model size:
$$R^2_{adj}=1-\frac{\mathrm{RSS}/(n-p)}{\mathrm{TSS}/(n-1)}$$
>It can fall when a predictor adds too little.

#### Variable selection
When many candidate predictors are available, variable selection searches for a smaller model, possible (eventually in conflict) **goals** are:
- Reducing measurement or data-collection cost
- Improving interpretability
- Reducing variance caused by unnecessary predictors
- Improving prediction when the full model overfits
>Selection does not find a "true" model and cannot replace scientific knowledge.

**Information criteria**
$\ell(\hat\theta)$ is the maximized log-likelihood, $k$ the number of estimated parameters, $n$ the sample size; smaller is better:
$$\mathrm{AIC}=-2\ell(\hat\theta)+2k,\qquad \mathrm{BIC}=-2\ell(\hat\theta)+k\log n .$$
The _first term rewards fit and the second penalizes complexity_.
- **AIC** ([Akaike Information Criterion](https://en.wikipedia.org/wiki/Akaike_information_criterion)) targets expected predictive loss
- **BIC** ([Bayesian Information Criterion](https://en.wikipedia.org/wiki/Bayesian_information_criterion)) approximates Bayesian model evidence in large samples

Neither is an absolute goodness-of-fit test, and since $\log n>2$ for $n\ge 8$, BIC penalizes complexity more heavily.

**Forward selection**: start from the intercept-only model, then at each step:
1. Add each currently excluded candidate term in turn
2. Compute the chosen criterion
3. Retain the addition producing the greatest decrease
4. Stop when no allowed addition improves the criterion

**Backward elimination**: start from the full candidate model, then at each step:
1. Remove each currently included candidate term in turn
2. Compute the chosen criterion
3. Retain the deletion producing the greatest decrease
4. Stop when no allowed deletion improves the criterion

---
### Model specifications
#### Qualitative predictors
Considering the mtcars dataset, `am` indicates transmission type, with automatic transmission as the reference group and $Y$ the fuel consumption we have:
$$\mathbb E(Y\mid\text{manual})=\beta_0+\beta_1\mathbf 1\{\text{manual}\}$$
A factor with $K$ levels becomes $K-1$ **indicator (dummy) columns**, and the omitted level is the reference.

#### Interactions
An interaction lets one predictor's effect depend on another:
$$\mathbb E(Y\mid X_1,X_2)=\beta_0+\beta_1X_1+\beta_2X_2+\beta_3X_1X_2$$

#### Polynomial terms
A quadratic mean function is still a linear model in its coefficients:
$$\mathbb E(Y|x)=\beta_0+\beta_1x+\beta_2x^2$$

---
### Diagnostics and computation
Diagnostics check whether the model is adequate for its purpose.

Main problems include: 
- Nonlinearity of the conditional mean
- Nonconstant error variance and dependent errors
- High-leverage or influential observations
- Collinearity

`plot(model)` gives **four standard plots**:
- _Residuals vs fitted_: curvature suggests a misspecified mean, a funnel shape suggests heteroscedasticity, and isolated points suggest outliers
- _Normal Q–Q_: points should follow the diagonal, normality matters mainly for exact small-sample t/F inference and prediction intervals
- _Scale–location_: plots $\sqrt{|r_i|}$ ($r_i$ = standardized residual) against fitted values, a trend means the variance changes
- _Residuals vs leverage_: identifies influential observations (discussed below)
![[LR model standard plots.png|608]]
#### Leverage and influence
The **fitted response vector** is:
$$\hat{\mathbf Y}=\mathbf X\hat{\boldsymbol\beta}=\underbrace{\mathbf X(\mathbf X^\top\mathbf X)^{-1}\mathbf X^\top}_{\mathbf H}\mathbf Y$$

$H$ is the **hat matrix**, which maps observed to fitted values.
Its diagonal entries $h_{ii}=\mathbf x_i^\top(\mathbf X^\top\mathbf X)^{-1}\mathbf x_i$ are the **leverages**, with $0\le h_{ii}\le1$ and $\sum_i h_{ii}=p$.

_High leverage_ means the predictor values $\mathbf x_i$ are unusual compared with the rest of the data.
>It does not mean the point is badly fitted.

Raw residuals have unequal variance, $\operatorname{Var}(e_i\mid\mathbf X)=\sigma^2(1-h_{ii})$, so we use **internally studentized residuals**:
$$r_i=\frac{e_i}{s\sqrt{1-h_{ii}}} .$$

**Externally studentized** residuals use an $s$ computed with observation $i$ deleted (`rstudent()`).

An **influential point** typically combines high leverage with a large residual.
**Cook's distance** measures how much the coefficient vector changes when observation $i$ is deleted:
$$D_i=\frac{e_i^2}{p\,s^2}\cdot\frac{h_{ii}}{(1-h_{ii})^2}$$
Rules such as $D_i>4/n$ are screening heuristics for outliers.

![[LR residuals vs leverage.png|514]]
#### Heteroscedasticity and autocorrelation
Let's write $\operatorname{Var}(\boldsymbol\varepsilon\mid\mathbf X)$ as $\Omega$, the classical assumption is $\Omega=\sigma^2\mathbf I$, and it can fail in two ways:
- **Heteroscedasticity**: the diagonal of $\Omega$ is not constant
- **Autocorrelation**: off-diagonal entries are nonzero (time-ordered, spatial or clustered data)

If $\mathbb E(\boldsymbol\varepsilon\mid\mathbf X)=\mathbf 0$ still holds, OLS remains **unbiased**, but $\operatorname{Var}(\hat{\boldsymbol\beta}\mid\mathbf X)\neq\sigma^2(\mathbf X^\top\mathbf X)^{-1}$, so the usual standard errors, tests and CIs are wrong.
The fix is a **sandwich estimator**, which keeps the estimates and changes only the variance estimate:
$$\widehat{\operatorname{Var}}(\hat{\boldsymbol\beta})=\underbrace{(\mathbf X^\top\mathbf X)^{-1}}_\text{"bread"}\,\underbrace{\mathbf X^\top\hat\Omega\mathbf X}_{\text{"meat"}}\,\underbrace{(\mathbf X^\top\mathbf X)^{-1}}_\text{"bread"}$$
- **HC1** (errors uncorrelated, unequal variances): $\hat\Omega=\frac{n}{n-p}\operatorname{diag}(e_1^2,\dots,e_n^2)$
- **HAC / Newey–West** (also autocorrelated): the "meat" becomes
$$\hat S=\sum_{t=1}^n e_t^2\mathbf x_t\mathbf x_t^\top+\sum_{j=1}^{L}w_j\sum_{t=j+1}^n e_te_{t-j}\big(\mathbf x_t\mathbf x_{t-j}^\top+\mathbf x_{t-j}\mathbf x_t^\top\big),\quad w_j=1-\frac{j}{L+1}$$

The first term is the HC meat, the second adds estimated autocovariances up to lag $L$ (the truncation parameter), down-weighted by the Bartlett weights $w_j$, which keep $\hat S$ positive semidefinite.
>A rule of thumb is $L=\lfloor 4(n/100)^{2/9}\rfloor$.

#### Collinearity
**Collinearity** means a predictor is _nearly a linear combination of the others_. 

It can produce:
- Large coefficient standard errors
- Unstable coefficients and signs
- Sensitivity to small data changes
- Difficulty separating partial effects

The **variance inflation factor** for predictor $X_j$ is
$$\mathrm{VIF}_j=\frac1{1-R_j^2},$$

where $R_j^2$ comes from regressing $X_j$ on all the other predictors.
>Values above about 3–5 indicate notable collinearity.

#### Training vs. generalization error
The training mean squared error (training MSE) measures _how closely a model fits the observations used to train it_:
$$\mathrm{MSE}_{train}=\frac1n\sum_{i=1}^n(y_i-\hat y_i)^2$$

it is computed on the data used to fit the model, so it underestimates error on new data.
>To judge generalization, evaluate on held-out data or use cross-validation.

