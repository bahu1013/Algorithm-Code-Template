A matroid is an ordered pair M = (S,ℓ) satisfying the following conditions.
1.	S is a finite nonempty set.
2.	ℓ is a nonempty family of subsets of S, called the independent subsets of S, such that if B ∈ℓ and A ⊆ B, then A ∈ℓ. We say thatℓ is hereditary if it satisfies this property. Note that the empty set Ø is necessarily a member of ℓ.
3.	If A ∈ℓ, B ∈ℓ, and |A| < |B|, then there is some element x ∈ B - A such that A ∪ {x} ∈ℓ. We say that M satisfies the exchange property.

Greedy on Weighted Matroid

GREEDY(M, w)
1  A ← Ø
2  sort S[M] into monotonically decreasing order by weight w
3  for each x S[M], taken in monotonically decreasing order by weight w(x)
4       do if A ∪ {x} ∈ℓ[M]
5             then A ← A ∪ {x}
6  return A
