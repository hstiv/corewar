.name "forker"
.comment "just a basic forker program"

l2:
	sti r1, %:fork, %1
	and r1, %0, r1
fork:
	live %1
	lfork %1537
	lfork %-1537
	zjmp %:fork
