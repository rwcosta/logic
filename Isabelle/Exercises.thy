theory Exercises
imports Main
begin

theorem first: 
  assumes pqr: "(P \<longrightarrow> Q) \<or> R"
    and pr: "P \<longrightarrow> \<not>R"
  shows "P \<longrightarrow> Q"
proof -
  have imp: "P \<Longrightarrow> Q"
  proof -
    assume p: "P"
    from pr and p have r: "\<not>R" by (rule impE)
    from pqr and r have pq: "P \<longrightarrow> Q" by (rule disjE)
    from pq and p show "Q" by (rule impE)
  qed
  from this show "P \<longrightarrow> Q" by (rule impI)
qed

theorem second:
  shows  "(A \<and> A) \<longrightarrow> A"
proof -
  have imp: "(A \<and> A) \<Longrightarrow> A"
  proof -
    assume aa: "A \<and> A"
    from aa show "A" by (rule conjE)
  qed
  from this show "(A \<and> A) \<longrightarrow> A" by (rule impI)
qed

end
