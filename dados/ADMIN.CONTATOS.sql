CREATE TABLE "ADMIN"."CONTATOS" 
   (	"ID_PESSOA" NUMBER, 
	"CPF" VARCHAR2(4000 BYTE) COLLATE "USING_NLS_COMP", 
	"DOC2" VARCHAR2(4000 BYTE) COLLATE "USING_NLS_COMP", 
	"TP_DOC2" VARCHAR2(4000 BYTE) COLLATE "USING_NLS_COMP", 
	"NOME" VARCHAR2(4000 BYTE) COLLATE "USING_NLS_COMP", 
	"DT_NASCIMENTO" TIMESTAMP (6), 
	"MAE" VARCHAR2(4000 BYTE) COLLATE "USING_NLS_COMP", 
	"PAI" VARCHAR2(4000 BYTE) COLLATE "USING_NLS_COMP", 
	"EMAIL" VARCHAR2(4000 BYTE) COLLATE "USING_NLS_COMP", 
	"TELEFONE1" VARCHAR2(4000 BYTE) COLLATE "USING_NLS_COMP", 
	"TELEFONE2" VARCHAR2(4000 BYTE) COLLATE "USING_NLS_COMP", 
	"FUNCAO" VARCHAR2(4000 BYTE) COLLATE "USING_NLS_COMP"
   )  DEFAULT COLLATION "USING_NLS_COMP" ;

CREATE UNIQUE INDEX "ADMIN"."CONTATOS_PK" ON "ADMIN"."CONTATOS" ("ID_PESSOA") 
  ;

ALTER TABLE "ADMIN"."CONTATOS" ADD CONSTRAINT "CONTATOS_PK" PRIMARY KEY ("ID_PESSOA")
  USING INDEX  ENABLE;

