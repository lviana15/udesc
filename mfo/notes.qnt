module notes {
    var grande: int
    var pequeno: int

    action enche_grande = all {
        grande' = 5,
        pequeno' = pequeno,
    }

    action enche_pequeno = all  {
        pequeno' = 3,
        grande' = grande,
    }

    action esvazia_grande = all {
        grande' = 0,
        pequeno' = pequeno
    }

    action esvazia_pequeno = all {
        pequeno' = 0,
        grande' = grande,
    }

    action grande_pro_pequeno = {
        if (pequeno + grande <= 3) all {
            pequeno' = pequeno + grande,
            grande' = 0,
        } else all {
            pequeno' = 3,
            grande' = pequeno - (3 - grande),
        }
    }

    action pequeno_pro_grande = all {
        if (pequeno + grande <= 5) all {
            grande' = pequeno + grande,
            pequeno' = 0,
        } else all {
            grande' = 5,
            pequeno' = grande - (5 - pequeno),
        }
    }

    action init = all {
        pequeno' = 0,
        grande' = 0
    }

    action step = any {
        enche_grande,
        enche_pequeno,
        esvazia_grande,
        esvazia_pequeno,
        pequeno_pro_grande,
        grande_pro_pequeno,
    }

    val inv = grande != 4

    run solution =
      init
        .then ( enche_grande )
        .then ( grande_pro_pequeno )
        .then ( esvazia_pequeno )
        .then ( grande_pro_pequeno )
        .then ( enche_grande )
        .then ( grande_pro_pequeno )
        .expect ( grande == 4)
}