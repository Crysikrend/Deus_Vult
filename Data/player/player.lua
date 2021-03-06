local entity = {
    player = {
        SpineComponent = {
            dataIsJSON = false,
            atlas = "common/spine/hero/export/hero.atlas",
            data = "common/spine/hero/export/hero.skel",
            defaultAnim = "idle",
            timeScale = 1,
            defaultMix = 0.2,
            animations = {
                idle = {
                    animString = "Idle"
                },
                walk = {
                    animString = "Walk"
                },
                run = {
                    animString = "Run"
                },
                attack = {
                    animString = "Attack"
                },
                crouch = {
                    animString = "Crouch"
                },
                fall = {
                    animString = "Fall"
                }
            }
        },
        OutlineComponent = {
            thickness = 5,
            colour = {100, 100, 255, 200},
        },
        TransformComponent = {
            position = {
                -9000, 300
            },
            scale = {
                0.5, 0.5
            },
            rotation = 0
        },
        MovementComponent = {
            maxSpeed = 2500,
            acceleration = 5000
        },
		CombatComponent = {
			health = {
				value = 100
			},
			actionPoints = {
				value = "sample text"
			}
		}
    }
}

return entity
