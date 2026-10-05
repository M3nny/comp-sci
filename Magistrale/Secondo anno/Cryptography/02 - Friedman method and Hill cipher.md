### Friedman method
Even if [[01 - Polyalphabetic ciphers#Polyalphabetic ciphers|Vigenére cipher]] hides the statistic structure of the plaintext better than [[01 - Polyalphabetic ciphers#Substitution cipher|monoalphabetic ciphers]], it still preserves most of it, we illustrate a method from **Wolfe Friedman** used to break it, which is composed by two steps:
1. Recover the length $m$ of the key
2. Recover the key

We sue the **index of coincidence** $I_c(x)$ which is a statistical measure that gives the probability that two letters, chosen at random from the text, are the same.
$$I_c(x)=\frac{\sum_{i=1}^{26}f_i(f_i-1)}{n(n-1)}\approx\sum_{i=1}^{26}p_i^2$$
>[!Example]
>Given `the index of coincidence`, its $I_c$ would be:
>`c(3*2)+ d(2*1)+ e(4*3)+ f(1*0)+ h(1*0)+ i(3*2)+ n(3*2)+ o(2*1)+ t(1*0)+ x(1*0) = 34`
>
>Which divided by $n(n-1)=21*20=420$ gives us: $I_c=34/420=0.0809$.

The $I_c$ is maximum ($=1$) when there is only one repeated letter over the whole text, and it is minimum ($=1/26$) when each letter is chosen with _uniform probability_.

Every language has its own $I_c$, English for example has a value of approximately $0.065$, based on this we can **distinguish between mono/poly-alphabetic ciphers**.
If a ciphertext has the minimum $I_c$, then we can assume it is polyalphabetic otherwise if it is equal to a language's $I_c$, it is monoalphabetic.

In order to **retrive the key length $m$**:
1. Start with a small value of $m$
2. Split the ciphertext into $m$ subtexts, taking every $m$-th letter
3. Calculate the $I_c$ for each subtext
4. Check whether all $I_c$ values are above $0.06$ (close to the expected English value)
5. If any $I_c$ is below $0.06$, increase $m$ by $1$ and repeat
6. When every $I_c$ passes the test, output that $m$

Now that we have the key:
1. Divide the text into blocks of length $m$
2. Build new cryptoprograms with the $i$-th letter of each block
3. Analyze the new cryptoprograms as before to find the shift in each position
>In practice: we consider a text composed of letter at distance $m$ from the first one and the ones at distance $m$ from the second one, and so on.
>They have different shifts, how can we find the relative right shift?

![[Wolfe Friedman.png|426]]
We find the relative shift between two subciphers of length $n$ and $n'$ by using the **mutual index of coincidence**:
$$MI_c(x,x')=\frac{\sum_{i=1}^{26}f_if'_i}{nn'}=\sum_{i=1}^{26}p_ip'_i$$
representing the probability that two letters taken from texts $x$ and $x'$ are the same.

The idea is to shift one subcipher until the mutual index of coincidence with the first subcipher becomes close to the one of the plaintext language:
1. For each key position $i$, take the corresponding subtext `sub[i]`
2. Try all 26 possible shifts $j=0,... ,25$
3. For each shift, calculate $MI_c$ between the first subtext `sub[0]` and the shifted subtext
4. Choose the shift $j$ that gives the highest $MI_c$
5. Add this best shift to `key`
6. Repeat for every position of the key
>It determines the individual letters/shifts of the Vigenére key by finding which shift makes each subtext most similar to the first subtext.

>[!Example]
>`key = [0,4,6,3,9]` means that the second letter of the key is equal to the first plus 4 while the third is the first plus 6 and so on.

### Known-plaintext attacks
So far we considered attackers that only know the ciphertext $y$ and try to find either the plaintext $x$ or the key $k$, but it is often the case that an attacker can _guess part of the plaintext_ (e.g. the standard header of  a message).

If a message is split into blocks which are encrypted under the same key, and if a key is reused to encrypt many plaintexts, it can occur that in the future, one of the plaintexts is leaked, thus giving the attacker knowledge of a pair $(x,y)$ plaintext, ciphertext.

We will consider the **known-plaintext attack**, that is: assume the attacker knows some pairs $(x',y'), (x'',y''), ...$ of plaintexts/ciphertexts.
>Given $y$ we're going to find the relative $x$ or $k$.

### The Hill cipher
The cipher is polyalphabetic and generalizes the idea of Vigenére by introducing linear transformations of blocks of plaintext.

To **encrypt** a message $M$, we have to:
- Take $M=(x_1,...,x_m)$ and the key $K$ which is an [[Triennale/Primo anno/Primo semestre/Algebra lineare/Matrici#Matrici inverse|invertible matrix]]
- Compute $(x_1,...,x_m)K\mod 26$

To **decrypt** a message $M$, we have to:
- Compute the inverse of $K$
- Compute $(y,...,y_m)K^{-1}\mod26$

>[!Example]
>$M=(5,9)$, $K=\begin{bmatrix}5&11\\8&3\end{bmatrix}$
>
>**Encrypt**
>$$\begin{align}
>E_k(5,9)&=(5,9)\times\begin{bmatrix}5&11\\8&3\end{bmatrix}\mod26\\
>&=(5\cdot5+9\cdot8,5\cdot11+9\cdot3)\mod26\\
>&=(97,82)\mod26\\
>&=(19,4)\\
>\end{align}$$
>
>**Decrypt**
>$det(K)=5$, now we want to find $det^{-1}(K)$, remembering that everything has to be $\mod26$, so to find the inverse $\mod26$ of $5$ we need to find a number in the interval $[0,25]$ that multiplied by $5\mod26$ gives $1$, that number in our case is $21$, hence $det^{-1}(K)=21$.
>>It is not always the case that the multiplicative inverse modulo exists, we will discuss this in detail when dealing with RSA.
>
>$$\begin{align}
>K^{-1}&=det^{-1}(K)\begin{bmatrix}5&11\\8&3\end{bmatrix}\mod26\\
>&=21\begin{bmatrix}5&11\\8&3\end{bmatrix}\mod26\\
>&=\begin{bmatrix}63&315\\378&105\end{bmatrix}\mod26\\
>&=\begin{bmatrix}11&3\\14&1\end{bmatrix}
>\end{align}$$
>
>$$\begin{align}
>D_k(19,4)&=(19,4)\begin{bmatrix}5&11\\8&3\end{bmatrix}\mod26\\
>&=(19\cdot11+4\cdot14,19\cdot3+4\cdot1)\mod26\\
>&=(265,61)\mod26\\
>&=(5,9)
>\end{align}$$


